```sh
ln -s ram.config .config
make
mv output/images/zImage output/images/zImage-ram

ln -s ext.config .config
make linux-reconfigure
make
mv output/images/zImage output/images/zImage-ext
```

* Copy output/images/rpi-firmware/\* and output/images/zImage\* to the sdcard.
* Make sure that config.txt has kernel set to zImage-ram.

* Boot the Pi.


Prepare partitions
------------------

```sh
mkdir /backup
cp /boot/* /backup
umount /boot

gdisk /dev/mmcblk0 # _ means "press enter without inputting anything"
	d
	n _ 4M +60M 0700
	n _ _ +1024M _
	n _ _ _ _

	r
		h 1 N b Y Y _
		w Y


mkfs.fat /dev/mmcblk0p1
mount -o rw /boot
cp /backup/* /boot
sync

reboot

mkfs.ext2 /dev/mmcblk0p3
```


Install the root filesystem
---------------------------

On the host:
```sh
scp output/images/rootfs.tar root@192.168.143.240:/ # Change IP to correct one
```

On the rpi:
```sh
mkfs.ext2 /dev/mmcblk0p2
mount /mnt
cd /mnt
tar -xvf /rootfs.tar
cd /
umount /mnt
```

Set the kernel in /boot/config.txt to zImage-ext.
```sh
reboot
```


Update the root filesystem
--------------------------

Set the kernel in /boot/config.txt to zImage-ram.
```sh
reboot
```

Follow the instructions for installing the root filesystem.


Build WWW application
---------------------
```sh
ln -s www.config .config
make
```
* Upload it to RPI as described in "Update the root filesystem".
* Use http://ip:8000/ to upload images and http://ip/ to view them.


Build rpiduino application
--------------------------
```sh
ln -s rpiduino.config .config
make
cd rpiduino; make; make install; cd ..
make
```
* Upload it to RPI as described in "Update the root filesystem".
* The presentation will start automatically.
