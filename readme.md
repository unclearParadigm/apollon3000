# Apollon3000

### Setup Rasbperry PI initially

##### TeamViewer

* Download TeamViewer from official Site
```bash
sudo dpkg -i teamviewer.deb
sudo apt install --fix-broken
sudo dpkg -i teamviewer.de
```


###### Install additional Tooling
```bash
sudo apt install git htop curl nano
```

* SSH is preinstalled already


###### Install Libraries for interacting with GPIOs
```bash
git clone git://git.drogon.net/wiringPi
./wiringPi/build
```
