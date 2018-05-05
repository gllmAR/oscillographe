En continuité avec le mouvement de musique pour oscilloscope, Oscillographe suscite une expérience sinestésique où son deviens l'image.



## Déploiement sur Raspberry pi

### Installation Arch linux via linux 

#### Partitions:
```
sudo fdisk /dev/sdX 
```

```
o -> clear 
p -> list partition
n -> new
p -> primary
1 -> first
accept default sector
+100M -> last 
	(remove signature yes)
t -> type
c -> W95 AT32 (LBA)
n -> new
p -> primary
2 -> second
accept default start sector
accept default end sector
w -> write
```

#### create file system
```
sudo mkfs.vfat /dev/sdX1
mkdir boot
sudo mount /dev/sdX1 boot
```

```
sudo mkfs.ext4 /dev/sdX2
mkdir root
sudo mount /dev/sdX2 root

```

#### deploy file system
```
wget http://os.archlinuxarm.org/os/ArchLinuxARM-rpi-2-latest.tar.gz
sudo bsdtar -xpf ArchLinuxARM-rpi-2-latest.tar.gz -C root
sync
sudo mv root/boot/* boot
sudo umount boot root
```

### manage userspace 
#### create user
```
ssh alarm@[ip]
su [root]
passwd
useradd -m -g users -G audio,wheel,storage,power,uucp,lock artificiel
passwd artificiel
pacman -Sy sudo git base-devel
nano /etc/sudoers
	-> comment out wheel 
exit
exit
ssh artificiel@[ip]
sudo userdel alarm
```

#### get ssh id
```
mkdir ~/aur && cd ~/aur
git -c http.sslVerify=false clone https://gitlab.artificiel.org:30000/aur/rsa-cloudclient.git 
cd rsa-cloudclient 
./pre-makepkg.sh
makepkg -sri
./install.sh

```
#### get maja 
cd ~/aur 
git clone ssh://git@gitlab.artificiel.org:30001/aur/maja.git
cd maja
./install.sh

#### get dependency via maja
maja -i -g ssh://git@gitlab.artificiel.org:30001/aur/core-system.git
maja -i -g ssh://git@gitlab.artificiel.org:30001/aur/openframeworks-git.git


