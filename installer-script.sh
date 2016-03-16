#!/bin/bash

# use: ./installer-script.sh [[--major|-ma] [--minor|-mi] | [--patch|-pa] | [--help|-h]]
# if -major then it is a major update
# if -minor then it is a minor update
# if -patch or no arguments given at all then it is a patch update

# 1. make sure you have the VST SDK from http://www.steinberg.net/en/company/developers.html, if you don't download it,
# and in the Introjucer > Tools > Global Preferences copy the path where you've download it. 
# 2. make sure the schemes are ticked to Shared in XCode > Product > Scheme > Manage Schemes
# 3. you are ready to go!

# reads from .version file the last version
CURRENT_MAJOR=$(cat .version | sed -n 1p);
CURRENT_MINOR=$(cat .version | sed -n 2p);
CURRENT_PATCH=$(cat .version | sed -n 3p);
TEMP_PLUGIN=~/synister
INFOPLIST_FILE=Info.plist
TEMP_STANDALONE=~/synister_standalone
STANDALONE_DIR=standalone/Builds/MacOSX
PLUGIN_DIR=plugin/Builds/MacOSX
PATCHES_DIR=inst-patchfiles
SCRIPTS_DIR=installer-mac/Scripts

usage() {
    echo 'Usage: ./installer-script.sh [[--major|-ma] [--minor|-mi] | [--patch|-pa] | [--help|-h]]
        Before you run it: 
        1. make sure you have the VST SDK from http://www.steinberg.net/en/company/developers.html, if you do not have it, download it,
        and in the Plugin Introjucer > MacOSX Configuration > VST copy the path where you have download it. 
        2. make sure the schemes are ticked to Shared in XCode > Product > Scheme > Manage Schemes
        3. you are ready to go!';
}

echo '' > installer-errors.log

# if no arguments were given, then it is only a patch update
if [ $# -gt 0 ]; then
	# otherwise it can be a major, minor or patch
	for i in "$@"
	do
  	case $i in
	--major|-ma)
      		echo "Major update" 2>> /dev/null
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
		usage;
		exit 1;
		;;
	*)
		usage;
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

STANDALONE_PROJECT_VERSION_NUMBER=$(/usr/libexec/PlistBuddy -c "Print CFBundleShortVersionString" "${STANDALONE_DIR}/${INFOPLIST_FILE}")
PLUGIN_PROJECT_VERSION_NUMBER=$(/usr/libexec/PlistBuddy -c "Print CFBundleShortVersionString" "${PLUGIN_DIR}/${INFOPLIST_FILE}")
JUCE_VERSION="version=\"$VERSION\""

if [ "$VERSION" != "$STANDALONE_PROJECT_VERSION_NUMBER" ]; then
    echo 'Updating standalone version number..';
    /usr/libexec/PlistBuddy -c "Set :CFBundleVersion $VERSION" "${STANDALONE_DIR}/${INFOPLIST_FILE}"
    /usr/libexec/PlistBuddy -c "Set :CFBundleShortVersionString $VERSION" "${STANDALONE_DIR}/${INFOPLIST_FILE}"
    sed -i -e 's/version="\([0-9].*\.[0-9].*\.[0-9].*\)"/'$JUCE_VERSION'/g' standalone/standalone.jucer
fi

if [ "$VERSION" != "$PLUGIN_PROJECT_VERSION_NUMBER" ]; then
    echo 'Updating plugin version number..';
    /usr/libexec/PlistBuddy -c "Set :CFBundleVersion $VERSION" "${PLUGIN_DIR}/${INFOPLIST_FILE}"
    /usr/libexec/PlistBuddy -c "Set :CFBundleShortVersionString $VERSION" "${PLUGIN_DIR}/${INFOPLIST_FILE}"
    sed -i -e 's/version="\([0-9].*\.[0-9].*\.[0-9].*\)"/'$JUCE_VERSION'/g' plugin/plugin.jucer
fi

echo "Package version: $VERSION"
echo ""
echo 'Creating packages directories..'
# creates directories where all the package are going to be created

mkdir "${TEMP_PLUGIN}" &> /dev/null
mkdir "${TEMP_PLUGIN}/VST" &> /dev/null
mkdir "${TEMP_PLUGIN}/Components" &> /dev/null

mkdir "${TEMP_STANDALONE}" &> /dev/null
mkdir "${TEMP_STANDALONE}/Applications" &> /dev/null

cp -rp "$PATCHES_DIR" "${TEMP_STANDALONE}"
mv "${TEMP_STANDALONE}/${PATCHES_DIR}" "${TEMP_STANDALONE}/Patches"

cp -rp "$PATCHES_DIR" "${TEMP_PLUGIN}"
mv "${TEMP_PLUGIN}/${PATCHES_DIR}" "${TEMP_PLUGIN}/Patches"

# deletes all current builds to avoid permissions problems
rm -rf "${STANDALONE_DIR}/build/Release";
rm -rf "${PLUGIN_DIR}/build/Release";

# -------- STANDALONE ----------

# creates archive of standalone
echo 'Creating archive of standalone..'
xcodebuild -project "${STANDALONE_DIR}/standalone.xcodeproj" -scheme standalone -configuration Release archive -archivePath "$(pwd)/standalone" > /dev/null 2>> installer-errors.log 

# gets the archive path
ARCHIVE=$(ls -t | grep xcarchive | sed -n 1p)

echo 'Exporting archive..'
xcodebuild -exportArchive -exportFormat APP -archivePath "$(pwd)/${ARCHIVE}" -exportPath "${TEMP_STANDALONE}/Applications/synister" > /dev/null 2>> installer-errors.log 

rm -rf "$ARCHIVE"

# -------- PLUGIN ----------

# creates a release build of the plugin; archive needed but not to be exported

echo 'Creating archive of plugin..'
#
xcodebuild -project "${PLUGIN_DIR}/synister.xcodeproj" -scheme synister -configuration Release archive > /dev/null 2>> installer-errors.log

cp -r "${PLUGIN_DIR}/build/Release/Components" "${TEMP_PLUGIN}"
cp -r "${PLUGIN_DIR}/build/Release/VST" "${TEMP_PLUGIN}"

echo 'Creating application package..'
# creates application package
pkgbuild --install-location / --scripts "${SCRIPTS_DIR}" --version "${VERSION}" --identifier de.tu-berlin.qu.synister.standalone --root "${TEMP_STANDALONE}" synister_standalone_build.pkg > /dev/null 2>> installer-errors.log

# creates plugin package
echo 'Creating plugin package..'
pkgbuild --install-location /Library/Audio/Plug-Ins --scripts "${SCRIPTS_DIR}" --version "${VERSION}" --identifier de.tu-berlin.qu.synister.plugin --root "${TEMP_PLUGIN}" synister_plugin_build.pkg > /dev/null 2>> installer-errors.log

echo 'Creating distribution files..'
# distribution files are for the personalized installer process
touch "${TEMP_PLUGIN}/distribution.xml"
chmod 777 "${TEMP_PLUGIN}/distribution.xml"
echo '<?xml version="1.0" encoding="utf-8"?>
<installer-gui-script minSpecVersion="1">
    <title>Synister</title>
    <license file="LICENSE.txt" mime-type="text/plain"/>
    <allowed-os-versions>
        <os-version min="10.7" />	
    </allowed-os-versions>
    <options customize="never" />
    <choices-outline>
        <line choice="install"/>
    </choices-outline>
    <choice id="install" visible="true" title="Install" description="Installation description goes here">
        <pkg-ref id="de.tu-berlin.qu.synister.plugin" version="'$VERSION'">synister_plugin_build.pkg</pkg-ref>
    </choice>
</installer-gui-script>
' > "${TEMP_PLUGIN}/distribution.xml"

touch "${TEMP_STANDALONE}/distribution.xml"
chmod 777 "${TEMP_STANDALONE}/distribution.xml"
echo '<?xml version="1.0" encoding="utf-8"?>
<installer-gui-script minSpecVersion="1">
    <title>Synister</title>
    <license file="LICENSE.txt" mime-type="text/plain"/>
    <allowed-os-versions>
        <os-version min="10.7" />
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
productbuild --resources $(pwd) --distribution "${TEMP_PLUGIN}/distribution.xml" --package-path $(pwd) synisterPlugin.pkg > /dev/null 2>> installer-errors.log
productbuild --resources $(pwd) --distribution "${TEMP_STANDALONE}/distribution.xml" --package-path $(pwd) synisterStandalone.pkg > /dev/null 2>> installer-errors.log

echo 'Deleting traces..'
# not needed files
rm -rf "${TEMP_PLUGIN}" > /dev/null 2>> installer-errors.log
rm -rf "${TEMP_STANDALONE}" > /dev/null 2>> installer-errors.log
rm -rf "${PLUGIN_DIR}/build/plugin.build" > /dev/null 2>> installer-errors.log
rm -rf "${STANDALONE_DIR}/build/standalone.build" > /dev/null 2>> installer-errors.log
rm synister_plugin_build.pkg > /dev/null 2>> installer-errors.log
rm synister_standalone_build.pkg > /dev/null 2>> installer-errors.log
