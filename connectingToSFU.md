# Connecting to wifi from command line

## Code Execution

Follow these steps:

1. 
```
systemctl status NetworkManager
sudo systemctl stop NetworkManager
sudo killall wpa_supplicant
sudo systemctl start NetworkManager
```
2. 
```
sudo nmcli connection add type wifi con-name "connection_name" ssid "ssid" -- wifi-sec.key-mgmt wpa-eap 802-1x.eap ttls 802-1x.anonymous-identity "computingid@sfu.ca" 802-1x.ca-cert "" 802-1x.phase2-auth pap 802-1x.identity "computingid@sfu.ca" 802-1x.password "password"

```
3.
```
sudo nmcli connection up "connection_name"
```

