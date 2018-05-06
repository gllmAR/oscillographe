En continuité avec le mouvement de musique pour oscilloscope, Oscillographe suscite une expérience sinestésique où son deviens l'image.

## [Oscillographe](http://gllmar.github.io/projets/oscillo/)


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

#### get ssh id (need a artificiel account)
```
mkdir ~/aur && cd ~/aur
git -c http.sslVerify=false clone https://gitlab.artificiel.org:30000/aur/rsa-cloudclient.git 
cd rsa-cloudclient 
./pre-makepkg.sh
makepkg -sri
./install.sh

```
#### get maja (need a artificiel account)
```
cd ~/aur 
git clone ssh://git@gitlab.artificiel.org:30001/aur/maja.git
cd maja
./install.sh
```

#### configure core system via maja (need a artificiel account)
```
maja -i -g ssh://git@gitlab.artificiel.org:30001/aur/core-system.git
```

#### configure hardware 
#### audio
```
sudo pacman -S alsa-utils
```
add to /boot/config.txt

```
dtparam=audio=on
audio_pwm_mode=2
```

video?
```
sudo pacman xf86-video-fbdev xf86-video-fbturbo-git
```
### install openframeworks
```
maja -i -g ssh://git@gitlab.artificiel.org:30001/aur/openframeworks-git.git
```

#### get libs for armv7
```
cd $OF_ROOT
cd /scripts/linux
sudo ./download_libs.sh --platform linuxarmv7l
cd /archlinux_armv7
sudo sh install_dependencies.sh
```

#### flags in profile
```
sudo nano /etc/profile.d/of_pi.sh
```
```
export MAKEFLAGS=-j4 PLATFORM_ARCH=armv7l PLATFORM_VARIANT=raspberry2
```
#### Get addons
```
cd $OF_ROOT
cd addons
git clone https://github.com/gllmAR/ofxBasicSoundPlayer

```

#### Clone this repo
```
mkdir ~/src && cd src 
git clone git@github.com:gllmAR/oscillographe.git

```

#### make the projet
```
cd oscillographe
make
```

### Troubleshoot
```
if software doesn't start, try to remove bin/data/setup.json
```