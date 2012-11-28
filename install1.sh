cp -R /mnt/browser/usb/drone_installer/kiss/usercode/ /mnt/kiss/

echo "Copied usercode..."

cp -R /mnt/browser/usb/drone_installer/kiss/jvm/ /mnt/kiss/

echo "Copied jni wrapper..."

cp /mnt/kiss/qt/lib/libts-1.0.so.0 /mnt/kiss/qt/lib/libts-0.0.so.0

echo "Copied libts..."

sync

echo "Synced"
