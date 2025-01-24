# Configuration

create myWifi.h in src include with the following content, containing your wifi credentials:

```cpp
#ifndef MYWIFI_H_
#define MYWIFI_H_

#define MY_WIFI_SSID "<ssid>"
#define MY_WIFI_PASSWORD "<wifi_password>"

#define NTP_SERVER "pool.ntp.org"

#endif
```

# Wiring Diagram

# Parts List

# 3D Printing

The 3D printing pars are available in the cad diretory and on [Printables](https://www.printables.com/model/1162687/).

# Editing the Digit Font

The font file as Affinity Designer file is available in the res directory. To convert the exported images to bitmaps you may use this [tool](https://javl.github.io/image2cpp/). Th bitmaps can be found in src/include/bitmaps.h.