#!/bin/bash

# use: ./installer-script.sh [[--major|-ma] [-minor|-mi] | [-patch|-pa] | [--help|-h]]
# if -major then it is a major update
# if -minor then it is a minor update
# if -patch or no arguments given at all then it is a patch update

# reads from .version file the last version
CURRENT_MAJOR=$(cat .version | sed -n 1p);
CURRENT_MINOR=$(cat .version | sed -n 2p);
CURRENT_PATCH=$(cat .version | sed -n 3p);
TEMP_PLUGIN=~/synister
INFOPLIST_FILE=Info.plist
TEMP_STANDALONE=~/synister_standalone
STANDALONE_DIR=standalone/Builds/MacOSX
PLUGIN_DIR=plugin/Builds/MacOSX

# if no arguments were given, then it is only a patch update
if [ $# -gt 0 ]; then
	# otherwise it can be a major, minor or patch
	for i in "$@"
	do
  	case $i in
	--major|-ma)
      		echo "Major update" 2> /dev/null
		((CURRENT_MAJOR++));
		CURRENT_MINOR=0;
		CURRENT_PATCH=0;
      		;;
	--minor|-mi)
		echo "Minor update" 2>> /dev/null
		((CURRENT_MINOR++));
		CURRENT_PATCH=0;
		;;
	--patch|-pa)
		echo "Patch update" 2>> /dev/null
		((CURRENT_PATCH++));
		;;
	--help|-h)
		echo 'Usage: ./installer-script.sh [[--major|-ma] [--minor|-mi] | [--patch|-pa] | [--help|-h]]';
		exit 1;
		;;
	*)
		echo 'Usage: ./installer-script.sh [[--major|-ma] [--minor|-mi] | [--patch|-pa] | [--help|-h]]';
		exit 1;
		;;
 	esac
	done
fi

# updates the version file
echo "\
$CURRENT_MAJOR
$CURRENT_MINOR
$CURRENT_PATCH" > .version

VERSION=${CURRENT_MAJOR}.${CURRENT_MINOR}.${CURRENT_PATCH};

/usr/libexec/PlistBuddy -c "Set :CFBundleVersion $VERSION" "${STANDALONE_DIR}/${INFOPLIST_FILE}"
/usr/libexec/PlistBuddy -c "Set :CFBundleShortVersionString $VERSION" "${STANDALONE_DIR}/${INFOPLIST_FILE}"

/usr/libexec/PlistBuddy -c "Set :CFBundleVersion $VERSION" "${PLUGIN_DIR}/${INFOPLIST_FILE}"
/usr/libexec/PlistBuddy -c "Set :CFBundleShortVersionString $VERSION" "${PLUGIN_DIR}/${INFOPLIST_FILE}"

echo "Package version: $VERSION"
echo ""
echo 'Creating packages directories..'
# creates directories where all the package are going to be created

sudo mkdir "${TEMP_PLUGIN}" &> /dev/null
sudo mkdir "${TEMP_PLUGIN}/VST" &> /dev/null
sudo mkdir "${TEMP_PLUGIN}/Components" &> /dev/null
sudo cp -r ~/Library/Audio/Plug-Ins/Components "${TEMP_PLUGIN}" &> /dev/null
sudo cp -r ~/Library/Audio/Plug-Ins/VST "${TEMP_PLUGIN}" &> /dev/null

sudo mkdir "${TEMP_STANDALONE}" &> /dev/null
sudo mkdir "${TEMP_STANDALONE}/Applications" &> /dev/null

# creates archive of standalone

echo 'Creating archive of standalone..'
sudo xcodebuild -project standalone/Builds/MacOSX/standalone.xcodeproj -scheme standalone -configuration Release archive > /dev/null 2>> installer-errors.log 

# gets the archive path
ARCHIVE_DIR=~/Library/Developer/Xcode/Archives/$(ls -t ~/Library/Developer/Xcode/Archives/ | sed -n 1p)
ARCHIVE=$(ls -t ${ARCHIVE_DIR}  | grep standalone | sed -n 1p) # fix me

echo 'Exporting archive..'
sudo xcodebuild -exportArchive -exportFormat APP -archivePath "${ARCHIVE_DIR}/${ARCHIVE}" -exportPath "${TEMP_STANDALONE}/Applications/synister" > /dev/null 2>> installer-errors.log 

# creates a release build of the plugin; archive is not working, because it doesn't copy the VST files

echo 'Creating archive of plugin..'
sudo xcodebuild -project plugin/Builds/MacOSX/plugin.xcodeproj -scheme plugin -configuration Release archive > /dev/null 2>> installer-errors.log

echo 'Creating application package..'
# creates application package
sudo pkgbuild --install-location / --version "${VERSION}" --identifier de.tu-berlin.qu.synister.standalone --root "${TEMP_STANDALONE}" synister_standalone_build.pkg > /dev/null 2>> installer-errors.log

# creates plugin package
echo 'Creating plugin package..'
sudo pkgbuild --install-location /Library/Audio/Plug-Ins --version "${VERSION}" --identifier de.tu-berlin.qu.synister.plugin --root "${TEMP_PLUGIN}" synister_build.pkg > /dev/null 2>> installer-errors.log

echo 'Creating distribution files..'
# distribution files are for the personalized installer process
sudo touch "${TEMP_PLUGIN}/distribution.xml"
sudo chmod 777 "${TEMP_PLUGIN}/distribution.xml"
echo '<?xml version="1.0" encoding="utf-8"?>
<installer-gui-script minSpecVersion="1">
    <title>Synister</title>
    <license file="LICENSE.txt" mime-type="text/plain"/>
    <allowed-os-versions>
        <os-version min="10.4" />	
    </allowed-os-versions>
    <options customize="never" />
    <choices-outline>
        <line choice="install"/>
    </choices-outline>
    <choice id="install" visible="true" title="Install" description="Installation description goes here">
        <pkg-ref id="de.tu-berlin.qu.synister.plugin" version="'$VERSION'">synister_build.pkg</pkg-ref>
    </choice>
</installer-gui-script>
' > "${TEMP_PLUGIN}/distribution.xml"

sudo touch "${TEMP_STANDALONE}/distribution.xml"
sudo chmod 777 "${TEMP_STANDALONE}/distribution.xml"
echo '<?xml version="1.0" encoding="utf-8"?>
<installer-gui-script minSpecVersion="1">
    <title>Synister</title>
    <license file="LICENSE.txt" mime-type="text/plain"/>
    <allowed-os-versions>
        <os-version min="10.4" />
    </allowed-os-versions>
    <options customize="never" />
    <choices-outline>
        <line choice="install"/>
    </choices-outline>
    <choice id="install" visible="true" title="Install" description="Installation description goes here">
        <pkg-ref id="de.tu-berlin.qu.synister.standalone" version="'$VERSION'">synister_standalone_build.pkg</pkg-ref>
    </choice>
</installer-gui-script>
' > "${TEMP_STANDALONE}/distribution.xml"

echo 'Finishing packages..'
# productbuild is used to create from the existing packages and the distribution files the personalised installer package
sudo productbuild --resources $(pwd) --distribution "${TEMP_PLUGIN}/distribution.xml" --package-path $(pwd) synister.pkg > /dev/null 2>> installer-errors.log
sudo productbuild --resources $(pwd) --distribution "${TEMP_STANDALONE}/distribution.xml" --package-path $(pwd) synisterStandalone.pkg > /dev/null 2>> installer-errors.log

echo 'Deleting traces..'
# not needed files
sudo rm -rf "${TEMP_PLUGIN}" > /dev/null 2>> installer-errors.log
sudo rm -rf "${TEMP_STANDALONE}" > /dev/null 2>> installer-errors.log
sudo rm -rf plugin/Builds/MacOSX/build/plugin.build > /dev/null 2>> installer-errors.log
sudo rm -rf standalone/Builds/MacOSX/build/standalone.build > /dev/null 2>> installer-errors.log
sudo rm synister_build.pkg > /dev/null 2>> installer-errors.log
sudo rm synister_standalone_build.pkg > /dev/null 2>> installer-errors.log
