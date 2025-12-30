D**فرآیند نصب SDL (یک کتابخانه گرافیکی برای باز کردن پنجره و مدیریت ماوس) در لینوکس:**

*   **پیدا کردن نسخه فعلی SDL2:** `apt-cache search libsdl2` (مثلاً: libsdl2-2.0-0)
*   **نصب SDL2:** `sudo apt-get install libsdl2-2.0-0` (نسخه پیدا شده را جایگزین کنید)
*   **نصب بسته توسعه (dev) SDL2:** `sudo apt-get install libsdl2-dev`
*   **در صورت نصب نبودن build-essential:** `sudo apt-get install build-essential`

---

**+ آدرس گیت‌هاب:** https://github.com/hadipic/evm-linux  

برای اجرای  شبیه ساز به شاخه bsp بروید و در انجا به شاخه سیمولیشن بروید  ردمی رو بخوانید این یک راهنمای جامع برای کامپایل و اجرای EVM Simulator روی ویندوز است. در زیر تمام مراحل به زبان فارسی به صورت واضح و گام‌به‌گام توضیح داده شده است :


## 1. EVM چیست؟

**`EVM`** مخفف **`Embedded Virtual Machine`** (ماشین مجازی توکار) است، یک چارچوب سازگار موتور اسکریپت‌نویسی عمومی. موتورهای اسکریپت‌نویسی که در حال حاضر پشتیبانی می‌شوند:

*   **pikascript:** یک موتور اسکریپت‌نویسی پایتون فوق سبک.
*   **quickjs:** یک موتور جاوااسکریپت توکار.
*   **mujs:** یک موتور جاوااسکریپت توکار.
*   **duktape:** یک موتور جاوااسکریپت توکار.
*   **jerryscript:** یک موتور جاوااسکریپت توکار.
*   **quickvm:** یک موتور اسکریپت‌نویسی عمومی توکار با کارایی بالا که توسط تیم EVM توسعه یافته است.



## 2. ساخت اکوسیستم برنامه‌های اینترنت اشیاء EVM



## 3. چارچوب برنامه کوچک EVUE

**`EVUE`** مخفف **`Embedded VUE`** است، یک چارچوب برنامه‌نویسی با دستوراتی شبیه به VUE که توسط تیم EVM برای دستگاه‌های توکار طراحی شده است. EVUE نه تنها ویژگی‌های برنامه‌نویسی کارآمد VUE را حفظ کرده، بلکه برای پلتفرم‌های توکار بهینه و سازگار شده است.

*   **کامپایل آنلاین، بدون کد C**
*   **پشتیبانی از چندین موتور اسکریپت‌نویسی**
*   **پشتیبانی از توسعه با چندین زبان** مانند جاوااسکریپت و پایتون
*   **چارچوب برنامه‌نویسی مبتنی بر داده**، با معماری MVVM
*   **پشتیبانی همزمان از توسعه سناریوهای با رابط کاربری و بدون رابط کاربری**

## 4. چشم‌انداز EVM

> **`اتصال همه چیز، به لطف ما ساده شد`**

**شکستن مرزهای مهارتی بین اینترنت اشیاء و اینترنت، توانمندسازی شرکت‌ها و توسعه‌دهندگان اینترنت اشیاء با مدل توسعه‌ای کاملاً جدید، کاهش سطح پیچیدگی توسعه اینترنت اشیاء و افزایش سرعت توسعه به شدت.**

## 5. ساختار دایرکتوری کد EVM

| فایل/پوشه | توضیح |
| :-------- | :-------- |
| **bsp** | دایرکتوری سازگاری با بردهای توسعه |
| **components** | دایرکتوری کامپوننت‌های شخص ثالث |
| **docs** | دایرکتوری منابع اسناد و تصاویر |
| **include** | دایرکتوری فایل‌های هدر |
| **engines** | موتورهای اسکریپت‌نویسی |
| **modules** | دایرکتوری ماژول‌ها |
| **test** | کدهای تست |
| **tools** | ابزارهای توسعه |
| **tutorial** | نمونه‌های آموزشی و راهنما |

## 6. راهنمای توسعه


*   [راهنمای آنلاین EVM در شاپ الکترونیک (www.shpelectronic.ir)](https://shop-electronic.ir/%d9%85%d8%a7%d8%b4%db%8c%d9%86-%d9%85%d8%ac%d8%a7%d8%b2%db%8c-%d8%ac%d8%a7%d9%88%d8%a7-%d8%a8%d8%b1%d8%a7%db%8c-%d8%a7%d9%85%d8%a8%d8%af-%d8%a8%d8%b1%d8%af%d9%87%d8%a7-evm-embedded-virtual-machi/)


## 7. مشارکت در کد

*   پروژه متن‌باز **`EVM`** را در حساب گیت‌هاب خود **Fork** کنید.
*   یک کپی از کد **`EVM`** را به صورت محلی **Clone** کنید.
*   پس از ایجاد تغییرات یا افزودن ویژگی جدید، آن را به شاخه راه‌دور (remote) fork شده خود **Push** کنید.
*   یک **Pull Request** ایجاد کنید و درخواست ادغام تغییرات خود را به شاخه توسعه اصلی **`EVM`** ارسال کنید.
*   تیم توسعه **`EVM`** به طور منظم کدها را بررسی کرده و پس از عبور از تست‌ها، آن‌ها را ادغام می‌کند.

## 8. پیوستن به EVM

فناوری آینده را می‌سازد. تیم **EVM** به مشارکت شما نیاز دارد. تیم **EVM** در حال حاضر از توسعه‌دهندگان جامعه با انگیزه و رویاپرداز برای همکاری در ایجاد اکوسیستم جدید اینترنت اشیاء دعوت به عمل می‌آورد.  
صرف نظر از پیشینه فنی شما، می‌توانید سهمی هرچند کوچک در رشد EVM داشته باشید. **تیم EVM به گرمی از شما استقبال می‌کند!**

#### 8.1 اتحادیه توسعه‌دهندگان اکوسیستم EVM

`اتحادیه توسعه‌دهندگان اکوسیستم EVM` یک گروه عمیق‌ از علاقه‌مندان و توسعه‌دهندگان است که توسط تیم EVM برای جامعه تشکیل شده است. در اینجا شما می‌توانید:

*   **همیشه** از جدیدترین تحولات فنی EVM مطلع باشید و کارآمدترین روش‌های توسعه اینترنت اشیاء را بیاموزید.
*   در **تعیین استراتژی آینده و برنامه‌ریزی مسیر توسعه** EVM مشارکت کنید.
*   از **تماس نزدیک و بدون واسطه با تیم EVM** بهره‌مند شوید و برای همکاری در آینده به EVM بپیوندید.
*   از **پشتیبانی فنی رایگان نسخه سازمانی EVM** و اشتراک‌گذاری آزادانه راه‌حل‌های فنی متنوع بهره‌مند شوید.

![QR Code گروه تلگرام evm]( @hadipic , https://t.me/esp32_evm)

> در صورت منقضی شدن QR کد گروه، لطفاً با شناسه تلگرام `@hadipic` تماس بگیرید و در یادداشت خود بنویسید: `[نام شما] -- علاقه‌مند به ماشین‌های مجازی -- [شهر شما]`. شما در اولین فرصت به گروه اضافه خواهید شد. با تشکر!



#### 8.2 فراخوان قهرمانان EVM (EVM Hero Recruitment)

EVM در مرحله رشد سریع استارتاپی قرار دارد. از افراد باانگیزه برای پیوستن و همکاری در گشودن افق جدیدی برای اکوسیستم اینترنت اشیاء استقبال می‌کند!

*   اگر به **فناوری ماشین‌های مجازی** یا **نحوه پیاده‌سازی یک زبان برنامه‌نویسی** علاقه‌مندید، ما از شما استقبال می‌کنیم.
*   اگر **درک و تجربه عمیقی از جاوااسکریپت، پایتون و زبان C** دارید، ما از شما استقبال می‌کنیم.
*   اگر **درک عمیقی از RTOSها دارید** و یک **توسعه‌دهنده حرفه‌ای C** هستید که هسته یک یا چند RTOS را به طور عمیق مطالعه کرده‌اید، ما از شما استقبال می‌کنیم.
*   اگر **بر پروتکل‌های مختلف اینترنت اشیاء و انتقال درایورها مسلط هستید**، ما از شما استقبال می‌کنیم.

**موقعیت مکانی: نیشابور**، شهری که قهرمانان از آن برمی‌خیزند!

علاقه‌مندان می‌توانند رزومه خود را به آدرس ایمیل ارسال کنند: **hdi.bashniji@gmail.com**. **به پیوستن شما خوش‌آمد می‌گوییم! حقوق، سهام، اختیار معامله (آپشن)؛ انتخاب با شما!**

#### 8.3 گروه رسمی بحث و تبادل نظر EVM در telegram

📦 لینک‌های مرجع و منابع

🔗 مخزن گیت‌هاب ESP32 EVM:

https://github.com/hadipic/evm-linux?tab=readme-ov-file

https://github.com/hadipic/esp32-evm-bin?tab=readme-ov-file

🔗 کانال تلگرام EVM:
https://t.me/esp32_evm
🔗 معرفی ماشین مجازی EVM در شاپ الکترونیک

https://shop-electronic.ir/ماشین-مجازی-جاوا-برای-امبد-بردها-evm-embedded-virtual-machi/
🔗لینک اپارات

https://aparat.com/v/ejyt63u


# 🏗️ **ساختار پروژه EVM-ESP32 - راهنمای کامل**

## 📋 **فهرست محتوا**

- [معرفی پروژه](#معرفی-پروژه)
- [ساختار دایرکتوری](#ساختار-دایرکتوری)
- [کامپوننت‌های اصلی](#کامپوننتهای-اصلی)
- [ماژول‌های EVM](#ماژولهای-evm)
- [موتورهای JavaScript](#موتورهای-javascript)
- [مدیریت سخت‌افزار](#مدیریت-سختافزار)
- [سیستم فایل](#سیستم-فایل)
- [شبکه و ارتباطات](#شبکه-و-ارتباطات)

---# 🏗️ **ساختار پروژه EVM-ESP32 - راهنمای کامل**
🔗 معرفی ماشین مجازی EVM در شاپ الکترونیک

https://shop-electronic.ir/ماشین-مجازی-جاوا-برای-امبد-بردها-evm-embedded-virtual-machi/

ساخت و تولید انواع مدارات الکترونیک @shop_electronic_bot
گروه esp32 
https://t.me/+oi9QrKR1qdozZTc0
سایت شاپ الکترونیک
https://shop-electronic.ir
گروه امبدد و کیوت
https://t.me/Embedded_Qt

🔗 کانال تلگرام EVM:
https://t.me/esp32_evm


🔗 مخزن گیت‌هاب ESP32 EVM:

https://github.com/hadipic/evm-linux?tab=readme-ov-file
https://github.com/hadipic/esp32-evm-bin?tab=readme-ov-file
https://github.com/hadipic/evm_java/tree/main





## 📋 **فهرست محتوا**

- [معرفی پروژه](#معرفی-پروژه)
- [ساختار دایرکتوری](#ساختار-دایرکتوری)
- [کامپوننت‌های اصلی](#کامپوننتهای-اصلی)
- [ماژول‌های EVM](#ماژولهای-evm)
- [موتورهای JavaScript](#موتورهای-javascript)
- [مدیریت سخت‌افزار](#مدیریت-سختافزار)
- [سیستم فایل](#سیستم-فایل)
- [شبکه و ارتباطات](#شبکه-و-ارتباطات)

---

## 🎯 **معرفی پروژه**

**EVM-ESP32** یک **Common Peripheral Framework** است که برای مدیریت یکپارچه سخت‌افزار در EVM طراحی شده. این پروژه امکان اجرای برنامه‌های JavaScript روی میکروکنترلر ESP32 را فراهم می‌کند.

    Embedded-VM یا Micro-VM
    ESP32-JavaScript-Runtime
    Dynamic-Firmware-ESP32


### ✨ **ویژگی‌های کلیدی**
- ✅ پشتیبانی از چندین موتور JavaScript
- ✅ ماژول‌های سخت‌افزاری کامل
- ✅ رابط کاربری گرافیکی با LVGL
- ✅ شبکه‌های مختلف (WiFi, MQTT, HTTP, FTP)
- ✅ مدیریت حرفه‌ای منابع

---

## 📁 **ساختار دایرکتوری**

```
evm-esp32/
├── 📁 main/                          # کدهای اصلی برنامه
│   ├── main.c                       # نقطه ورود اصلی
│   ├── evm_app_manager.c            # مدیریت برنامه‌ها
│   └── evm_app_manager.h            # هدر مدیریت برنامه‌ها
│
├── 📁 components/                   # کامپوننت‌های پروژه
│   ├── 📁 engines/                  # موتورهای JavaScript
│   ├── 📁 esp_modules/              # ماژول‌های EVM برای ESP32
│   ├── 📁 hardware_manager/         # مدیریت سخت‌افزار
│   ├── 📁 modules/                  # ماژول‌های عمومی
│   ├── 📁 lvgl/                     # کتابخانه LVGL
│   ├── 📁 lvgl_esp32_drivers/       # درایورهای LVGL برای ESP32
│   ├── 📁 lv-fs/                    # سیستم فایل LVGL
│   ├── 📁 mongoose/                 # کتابخانه شبکه Mongoose
│   ├── 📁 shared_hardware/          # سخت‌افزار مشترک
│   ├── 📁 webclient/                # کلاینت وب
│   ├── 📁 zmalloc/                  # مدیریت حافظه
│   ├── 📁 jsmn/                     # پارسر JSON
│   ├── 📁 libtuv/                   # کتابخانه LibTuv
│   └── 📁 include/                  # فایل‌های هدر عمومی
│
├── 📁 apps/                         # برنامه‌های کاربر
├── 📁 spiffs/                       # فایل‌های SPIFFS
└── 📁 build/                        # فایل‌های ساخت
```

---

## 🔧 **کامپوننت‌های اصلی**

### **۱. 📁 main/** - کدهای اصلی
- **`main.c`**: نقطه ورود اصلی برنامه
- **`evm_app_manager.c`**: مدیریت اجرای برنامه‌های JavaScript
- **`evm_app_manager.h`**: تعاریف و APIهای مدیریت برنامه

### **۲. 📁 components/** - کامپوننت‌های پروژه

#### **🔄 📁 engines/** - موتورهای JavaScript
```
engines/
├── 📁 quickjs/      # ✅ QuickJS (پشتیبانی از ES2020)
├── 📁 mujs/         # ✅ MuJS (پشتیبانی از ES5)  
├── 📁 jerryscript/  # ✅ JerryScript (پشتیبانی از ES5.1)
├── 📁 duktape/      # ✅ Duktape (پشتیبانی از ES5-ES6)
└── 📁 evm/          # ✅ EVM Core (هسته اصلی)
```

#### **⚡ 📁 esp_modules/** - ماژول‌های EVM برای ESP32
```
esp_modules/
├── evm_module_gpio.c        # کنترل پین‌های دیجیتال
├── evm_module_adc.c         # مبدل آنالوگ به دیجیتال
├── evm_module_pwm.c         # مدولاسیون عرض پالس
├── evm_module_i2c.c         # ارتباط I2C
├── evm_module_spi.c         # ارتباط SPI
├── evm_module_uart.c        # ارتباط سریال
├── evm_module_wifi.c        # مدیریت WiFi
├── evm_module_mongoose.c    # HTTP/WebSocket/MQTT
├── evm_module_fs.c          # سیستم فایل
├── evm_module_timer.c       # تایمر و زمان
├── evm_module_process.c     # اطلاعات سیستم
├── evm_module_dac.c         # مبدل دیجیتال به آنالوگ
├── evm_module_touch.c       # سنسور لمسی
├── evm_module_dma.c         # دسترسی مستقیم به حافظه
├── evm_module_mqtt.c        # پروتکل MQTT
├── evm_module_ftp.c         # سرور FTP
└── evm_module.c             # ثبت و مدیریت ماژول‌ها
```

#### **🔌 📁 hardware_manager/** - مدیریت سخت‌افزار
```
hardware_manager/
├── hardware_manager.c       # مدیریت اصلی سخت‌افزار
├── wifi_driver.c            # درایور WiFi
├── sd_card_driver.c         # درایور کارت SD
├── lcd101.c                 # درایور LCD
├── dual_storage.c           # مدیریت حافظه دوگانه
└── spiffs_driver.c          # درایور SPIFFS
```

#### **🎨 📁 modules/** - ماژول‌های عمومی
```
modules/
├── 📁 gui/
│   └── 📁 lvgl-js/         # ماژول‌های LVGL برای JavaScript
└── 📁 common/               # ماژول‌های مشترک بین پلتفرم‌ها
```

#### **🌐 📁 mongoose/** - کتابخانه شبکه
```
mongoose/
├── mqtt_broker.c            # MQTT Broker
├── mqtt_client.c            # MQTT Client  
├── http_server.c            # HTTP Server
├── ftp_server.c             # FTP Server
└── websocket_driver.c       # WebSocket Driver
```

---

## 🚀 **ماژول‌های EVM**

### **📋 لیست کامل ماژول‌های پیاده‌سازی شده**

| ماژول | وضعیت | توضیحات |
|-------|--------|----------|
| **Console** | ✅ کامل | کنترل خروجی و دیباگ |
| **FileSystem** | ✅ کامل | مدیریت فایل و دایرکتوری |
| **GPIO** | ✅ کامل | کنترل پین‌های دیجیتال |
| **Process** | ✅ کامل | اطلاعات سیستم و مدیریت پردازش |
| **Timer** | ✅ کامل | تایمر و زمان‌بندی |
| **WiFi** | ✅ کامل | اتصال شبکه و مدیریت WiFi |
| **ADC** | ✅ کامل | خواندن سنسورهای آنالوگ |
| **PWM** | ✅ کامل | کنترل موتور و LED |
| **I2C** | ✅ کامل | ارتباط با سنسورهای I2C |
| **SPI** | ✅ کامل | ارتباط با LCD و کارت حافظه |
| **UART** | ✅ کامل | ارتباط سریال |
| **Touch** | ✅ کامل | سنسورهای لمسی |
| **DAC** | ✅ کامل | تولید سیگنال آنالوگ |
| **DMA** | ✅ کامل | انتقال مستقیم حافظه |
| **Mongoose** | ✅ کامل | HTTP, WebSocket, MQTT |
| **MQTT** | ✅ کامل | پروتکل MQTT |
| **FTP** | ✅ کامل | انتقال فایل |
| **LVGL** | ✅ کامل | رابط کاربری گرافیکی |
| **IR-tx-rx** | ✅ کامل |دریافت ارسال ریموت کنترلهای ای ار سامسونگ الجی . |
| **RF-315-435** | ✅ کامل |دریافت و ارسال کد ریموت کد فیکس و کد لرن|
| **RF-HS300** | ✅ کامل  |دریافت و ارسال کدهای ریموت هاپینگ  کلیکتو|
| **ONE_WIR** | ✅ کامل | خواندن سنسورهای دما و رطوبت- خواندن نوشتن ایپرام وان وایر  |


---

## 🔄 **موتورهای JavaScript**

### **مقایسه موتورها**

| موتور | نسخه ES | سایز | کارایی | استفاده |
|-------|----------|------|--------|---------|
| **QuickJS** | ES2020 | ~400KB | ⭐⭐⭐⭐⭐ | برنامه‌های پیشرفته |
| **MuJS** | ES5 | ~200KB | ⭐⭐⭐ | برنامه‌های ساده |
| **JerryScript** | ES5.1 | ~200KB | ⭐⭐⭐ | دستگاه‌های محدود |
| **Duktape** | ES5-ES6 | ~300KB | ⭐⭐⭐⭐ | برنامه‌های متعادل |

---

## 🔌 **مدیریت سخت‌افزار**

### **سخت‌افزارهای پشتیبانی شده**

#### **📺 نمایشگر LCD**
- درایور LCD 160x128
- پشتیبانی از رابط SPI
- کنترل با ماژول LVGL

#### **📡 شبکه WiFi**
- حالت Station و Access Point
- اسکن شبکه‌های available
- اتصال خودکار

#### **💾 حافظه‌ها**
- **SPIFFS**: حافظه فلش داخلی
- **SD Card**: حافظه خارجی
- **PSRAM**: حافظه خارجی برای برنامه‌های بزرگ

#### **🔧 درایورهای سخت‌افزاری**
- GPIO (ورودی/خروجی دیجیتال)
- ADC (خواندن آنالوگ)
- PWM (کنترل موتور و LED)
- I2C (سنسورها)
- SPI (LCD و کارت حافظه)
- UART (ارتباط سریال)
- Touch (سنسور لمسی)
- DAC (خروجی آنالوگ)

---

## 💾 **سیستم فایل**

### **ساختار فایل‌های برنامه**

```
📁 apps/                 # برنامه‌های کاربر
├── calculator.js       # ماشین حساب
├── media_player.js    # پخش رسانه
├── game_pong.js       # بازی پونگ
├── weather_station.js # ایستگاه هواشناسی
├── iot_controller.js  # کنترل IoT
└── system_info.js     # اطلاعات سیستم

📁 spiffs/             # فایل‌های سیستم
├── config.json       # تنظیمات
├── main.js          # اسکریپت اصلی
└── assets/          # فایل‌های رسانه‌ای
```

### **مدیریت حافظه دوگانه**
```javascript
// نوشتن در SPIFFS
fs.writeFile("/config.json", '{"name":"test"}', fs.SPIFFS);

// نوشتن در SD Card  
fs.writeFile("/data.log", "log data", fs.SDCARD);

// کپی بین استوریج‌ها
fs.copyFile("/spiffs/config.json", "/sdcard/backup.json", fs.SPIFFS, fs.SDCARD);
```

---

## 🌐 **شبکه و ارتباطات**

### **پروتکل‌های پشتیبانی شده**

#### **📡 WiFi**
- Station mode (اتصال به شبکه)
- Access Point mode (ایجاد شبکه)
- اسکن شبکه‌های available

#### **🌐 HTTP/HTTPS**
- سرور HTTP برای REST API
- کلاینت HTTP برای درخواست‌های خارجی
- پشتیبانی از JSON

#### **📨 MQTT**
- Broker داخلی
- کلاینت MQTT
- پشتیبانی از QoS
- Callbackهای real-time

#### **📂 FTP**
- سرور FTP برای انتقال فایل
- احراز هویت کاربر
- مدیریت دایرکتوری

#### **🔗 WebSocket**
- ارتباط real-time دوطرفه
- پشتیبانی از text و binary data
- مدیریت اتصال‌های همزمان

---

## 🎯 **نمونه کد JavaScript**

### **برنامه ساده کنترل LED**
```javascript
// apps/led_controller.js
console.log("🚀 Starting LED Controller...");

const LED_PIN = 2;

// تنظیم پین به عنوان خروجی
gpio.setDirection(LED_PIN, gpio.OUTPUT);

// چشمک زدن LED
let counter = 0;
setInterval(() => {
    const state = counter % 2;
    gpio.write(LED_PIN, state);
    console.log(`💡 LED ${state ? 'ON' : 'OFF'} - Count: ${counter}`);
    counter++;
}, 1000);

// خواندن دکمه
setInterval(() => {
    const buttonState = gpio.readButton(gpio.BUTTON_UP);
    if (buttonState) {
        console.log("🔘 UP button pressed!");
    }
}, 100);
```

### **برنامه مانیتورینگ سیستم**
```javascript
// apps/system_monitor.js
console.log("📊 Starting System Monitor...");

setInterval(() => {
    const mem = process.memoryUsage();
    const cpu = process.cpuUsage();
    const heap = process.heapStats();
    
    console.log("=== System Status ===");
    console.log(`🧠 Memory: ${mem.usage.toFixed(1)}%`);
    console.log(`⚡ CPU: ${cpu.total.toFixed(1)}%`);
    console.log(`💾 Free Heap: ${(heap.free / 1024).toFixed(1)} KB`);
    console.log(`⏰ Uptime: ${process.uptime()}s`);
    
    // خواندن سنسور
    
}, 5000);
```

---

## 🔧 **کامپایل و اجرا**

### **کامپایل پروژه**
```bash
cd evm-esp32
idf.py set-target esp32
idf.py build
idf.py flash
idf.py monitor
```

### **پیکربندی سخت‌افزار**

#### **اتصالات SD Card**
| پین ESP32 | اتصال SD Card |
|-----------|---------------|
| GPIO 18   | CLK           |
| GPIO 19   | MISO          |
| GPIO 23   | MOSI          |
| GPIO 5    | CS            |

#### **اتصالات LCD**
| پین ESP32 | اتصال LCD |
|-----------|-----------|
| GPIO 15   | CS        |
| GPIO 13   | DIN       |
| GPIO 14   | CLK       |

#### **دکمه‌های کنترل**
| پین ESP32 | دکمه |
|-----------|------|
| GPIO 2    | UP   |
| GPIO 4    | SELECT |
| GPIO 34   | DOWN |
| GPIO 35   | BACK |

---

## 🎉 **نتیجه‌گیری**

**EVM-ESP32** یک پلتفرم کامل برای توسعه برنامه‌های JavaScript روی میکروکنترلرهاست که:

- ✅ **چندین موتور JavaScript** پشتیبانی می‌کند
- ✅ **ماژول‌های سخت‌افزاری کامل** ارائه می‌دهد  
- ✅ **رابط کاربری گرافیکی** با LVGL دارد
- ✅ **شبکه‌های مختلف** را پشتیبانی می‌کند
- ✅ **مدیریت حرفه‌ای منابع** انجام می‌دهد

این پروژه پایه‌ای قوی برای **سیستم‌های embedded مبتنی بر JavaScript** فراهم می‌کند! 🚀

---

کاملاً درست می‌فرمایید! بخش ویجت‌های اصلی را کامل به راهنما اضافه می‌کنم:

# 📚 **راهنمای کامل ماژول LVGL برای EVM - نسخه مدیریت حافظه**

## 🎯 **معرفی ماژول LVGL**

ماژول LVGL امکان ایجاد رابط کاربری گرافیکی روی ESP32 را فراهم می‌کند. این ماژول تمام ویجت‌های اصلی LVGL را پشتیبانی می‌کند.

---

## 🏗️ **ساختار اصلی**

### **ایجاد و مدیریت آبجکت‌ها**

```javascript
// ایجاد صفحه اصلی
let screen = lv.lv_scr_act();

// ایجاد آبجکت جدید
let obj = lv.lv_obj_create(screen);

// تنظیم موقعیت و سایز
lv.lv_obj_set_pos(obj, 10, 20);
lv.lv_obj_set_size(obj, 100, 50);
```

---

## 🔥 **مدیریت حافظه و تخریب آبجکت‌ها (جدید)**

### **تخریب ایمن آبجکت‌ها**

```javascript
// 🔥 روش صحیح تخریب آبجکت
let obj = lv.lv_obj_create(screen);
let style = lv.lv_style_create();

// تنظیم استایل و خصوصیات
lv.lv_obj_add_style(obj, style, 0);

// 🔥 تخریب صحیح آبجکت و استایل
lv.destroy_obj({
    nativePtr: obj,
    stylePtr: style
});

console.log("Object destroyed successfully!");
```

### **پاکسازی کامل تمام آبجکت‌ها**

```javascript
// 🔥 پاکسازی ایمن تمام آبجکت‌های صفحه
let count = lv.safe_destroy_all();
console.log("Destroyed " + count + " objects");

// 🔥 پاکسازی انتخابی
let parent = lv.lv_obj_create(screen);
// ایجاد چندین child
let child1 = lv.lv_obj_create(parent);
let child2 = lv.lv_obj_create(parent);

// پاکسازی تمام children های یک parent
lv.lv_obj_delete_all_children(parent);
```

### **توابع جدید مدیریت حافظه**

```javascript
// بررسی valid بودن آبجکت
if (lv.lv_obj_is_valid(obj)) {
    console.log("Object is valid");
} else {
    console.log("Object is invalid");
}

// تخریب فوری آبجکت
lv.lv_obj_del(obj);

// تخریب غیرهمزمان (برای جلوگیری از deadlock)
lv.lv_obj_del_async(obj);

// پاکسازی استایل
lv.lv_style_destroy(style);
```

---

## 🎨 **مدیریت استایل‌ها**
### **ترتیب صحیح کار با LVGL:**

1. **ایجاد استایل**
2. **مقداردهی اولیه استایل** (`init_style`)
3. **تنظیم خصوصیات استایل**
4. **اعمال استایل به آبجکت**
5. **تخریب استایل وقتی نیاز نیست**

```javascript
// ایجاد و مقداردهی استایل
let style = lv.lv_style_create();
lv.init_style(style); // 🔥 تابع جدید برای مقداردهی اولیه

// تنظیم خصوصیات
lv.set_style_bg_color(style, lv.lv_color_hex(0xFF0000));
lv.set_style_bg_opa(style, lv.LV_OPA_COVER);
lv.set_style_radius(style, 10);

// اعمال استایل
lv.lv_obj_add_style(obj, style, 0);

// 🔥 وقتی کارمان تمام شد:
lv.destroy_obj({
    nativePtr: obj,
    stylePtr: style
});
```

### **پالت رنگ‌های پیش‌فرض**

```javascript
// استفاده از پالت‌های پیش‌فرض
let red = lv.lv_palette_main(lv.LV_PALETTE_RED);
let blue = lv.lv_palette_main(lv.LV_PALETTE_BLUE);
let green = lv.lv_palette_main(lv.LV_PALETTE_GREEN);

// تبدیل RGB به رنگ LVGL
let customColor = lv.rgba_to_color(1.0, 0.5, 0.0, 1.0); // 🔥 تابع جدید
```

---

## 📋 **ویجت‌های اصلی**

### **۱. Label (متن)**

```javascript
// ایجاد لیبل
let label = lv.lv_label_create(screen);

// تنظیم متن
lv.lv_label_set_text(label, "Hello EVM!");

// تنظیم متن طولانی با اتوماتیک برش
lv.lv_label_set_long_mode(label, lv.LV_LABEL_LONG_SCROLL_CIRCULAR);

// تنظیم موقعیت
lv.lv_obj_set_pos(label, 10, 10);

// تنظیم استایل متن
let textStyle = lv.lv_style_create();
lv.init_style(textStyle);
lv.set_style_text_color(textStyle, lv.lv_color_hex(0xFFFFFF));
lv.set_style_text_font(textStyle, lv.lvgl_style_get_font(16)); // 🔥 انتخاب فونت
lv.lv_obj_add_style(label, textStyle, 0);

// 🔥 مدیریت حافظه
// بعد از استفاده:
lv.destroy_obj({
    nativePtr: label,
    stylePtr: textStyle
});
```

### **۲. Button (دکمه)**

```javascript
// ایجاد دکمه
let btn = lv.lv_btn_create(screen);
lv.lv_obj_set_size(btn, 80, 40);
lv.lv_obj_set_pos(btn, 50, 100);

// اضافه کردن متن روی دکمه
let btnLabel = lv.lv_label_create(btn);
lv.lv_label_set_text(btnLabel, "Click Me!");
lv.lv_obj_center(btnLabel);

// استایل دکمه
let btnStyle = lv.lv_style_create();
lv.init_style(btnStyle);
lv.set_style_bg_color(btnStyle, lv.lv_palette_main(lv.LV_PALETTE_BLUE));
lv.set_style_bg_opa(btnStyle, lv.LV_OPA_COVER);
lv.set_style_radius(btnStyle, 10);
lv.lv_obj_add_style(btn, btnStyle, 0);

// 🔥 ثبت event با مدیریت حافظه
lv.lv_obj_add_event_cb(btn, function(obj, event) {
    console.log("Button clicked! Event:", event);
}, lv.LV_EVENT_CLICKED);

// 🔥 تخریب ایمن
lv.destroy_obj({
    nativePtr: btn,
    stylePtr: btnStyle
});
```

### **۳. Slider (اسلایدر)**

```javascript
// ایجاد اسلایدر
let slider = lv.lv_slider_create(screen);
lv.lv_obj_set_size(slider, 150, 10);
lv.lv_obj_set_pos(slider, 20, 60);

// تنظیم محدوده
lv.lv_slider_set_range(slider, 0, 100);

// تنظیم مقدار اولیه
lv.lv_slider_set_value(slider, 50, lv.LV_ANIM_OFF);

// استایل اسلایدر
let sliderStyle = lv.lv_style_create();
lv.init_style(sliderStyle);
lv.set_style_bg_color(sliderStyle, lv.lv_palette_main(lv.LV_PALETTE_GREY));
lv.set_style_bg_opa(sliderStyle, lv.LV_OPA_50);
lv.set_style_outline_width(sliderStyle, 0);
lv.lv_obj_add_style(slider, sliderStyle, 0);

// event برای تغییر مقدار
lv.lv_obj_add_event_cb(slider, function(obj, event) {
    let value = lv.lv_slider_get_value(obj);
    console.log("Slider value:", value);
}, lv.LV_EVENT_VALUE_CHANGED);
```

### **۴. Switch (سوییچ)**

```javascript
// ایجاد سوییچ
let sw = lv.lv_switch_create(screen);
lv.lv_obj_set_pos(sw, 20, 160);

// استایل سوییچ
let switchStyle = lv.lv_style_create();
lv.init_style(switchStyle);
lv.set_style_bg_color(switchStyle, lv.lv_palette_main(lv.LV_PALETTE_GREEN));
lv.lv_obj_add_style(sw, switchStyle, 0);

// event برای تغییر وضعیت
lv.lv_obj_add_event_cb(sw, function(obj, event) {
    let isOn = lv.lv_obj_has_state(obj, lv.LV_STATE_CHECKED);
    console.log("Switch is:", isOn ? "ON" : "OFF");
}, lv.LV_EVENT_VALUE_CHANGED);
```

### **۵. Checkbox (چک‌باکس)**

```javascript
// ایجاد چک‌باکس
let cb = lv.lv_checkbox_create(screen);
lv.lv_obj_set_pos(cb, 20, 200);
lv.lv_checkbox_set_text(cb, "Enable Feature");

// استایل چک‌باکس
let checkboxStyle = lv.lv_style_create();
lv.init_style(checkboxStyle);
lv.set_style_text_color(checkboxStyle, lv.lv_color_hex(0x333333));
lv.lv_obj_add_style(cb, checkboxStyle, 0);

// event برای تغییر وضعیت
lv.lv_obj_add_event_cb(cb, function(obj, event) {
    let isChecked = lv.lv_obj_has_state(obj, lv.LV_STATE_CHECKED);
    console.log("Checkbox is:", isChecked ? "checked" : "unchecked");
}, lv.LV_EVENT_VALUE_CHANGED);
```

### **۶. Dropdown (لیست کشویی)**

```javascript
// ایجاد dropdown
let dropdown = lv.lv_dropdown_create(screen);
lv.lv_obj_set_pos(dropdown, 20, 240);
lv.lv_obj_set_size(dropdown, 120, 40);

// تنظیم گزینه‌ها
lv.lv_dropdown_set_options(dropdown, "Option 1\nOption 2\nOption 3\nOption 4");

// استایل dropdown
let dropdownStyle = lv.lv_style_create();
lv.init_style(dropdownStyle);
lv.set_style_bg_color(dropdownStyle, lv.lv_color_hex(0xF0F0F0));
lv.set_style_border_width(dropdownStyle, 1);
lv.set_style_border_color(dropdownStyle, lv.lv_color_hex(0xCCCCCC));
lv.lv_obj_add_style(dropdown, dropdownStyle, 0);

// event برای انتخاب گزینه
lv.lv_obj_add_event_cb(dropdown, function(obj, event) {
    let selected = lv.lv_dropdown_get_selected(obj);
    console.log("Selected option:", selected);
}, lv.LV_EVENT_VALUE_CHANGED);
```

### **۷. Textarea (ورودی متن)**

```javascript
// ایجاد textarea
let ta = lv.lv_textarea_create(screen);
lv.lv_obj_set_size(ta, 200, 60);
lv.lv_obj_set_pos(ta, 20, 280);

// تنظیم placeholder
lv.lv_textarea_set_placeholder_text(ta, "Enter text here...");

// تنظیم متن تک خطی
lv.lv_textarea_set_one_line(ta, true);

// استایل textarea
let textareaStyle = lv.lv_style_create();
lv.init_style(textareaStyle);
lv.set_style_bg_color(textareaStyle, lv.lv_color_hex(0xFFFFFF));
lv.set_style_border_width(textareaStyle, 1);
lv.set_style_border_color(textareaStyle, lv.lv_color_hex(0xCCCCCC));
lv.set_style_pad_all(textareaStyle, 8);
lv.lv_obj_add_style(ta, textareaStyle, 0);

// event برای تغییر متن
lv.lv_obj_add_event_cb(ta, function(obj, event) {
    let text = lv.lv_textarea_get_text(obj);
    console.log("Textarea content:", text);
}, lv.LV_EVENT_VALUE_CHANGED);
```

---

## 📊 **ویجت‌های پیشرفته**

### **Arc (پیشرفت دایره‌ای)**

```javascript
// ایجاد arc
let arc = lv.lv_arc_create(screen);
lv.lv_obj_set_size(arc, 100, 100);
lv.lv_obj_set_pos(arc, 50, 50);

// تنظیم محدوده و مقدار
lv.lv_arc_set_range(arc, 0, 100);
lv.lv_arc_set_value(arc, 75);

// تنظیم زوایا
lv.lv_arc_set_bg_angles(arc, 0, 270);

// استایل arc
let arcStyle = lv.lv_style_create();
lv.init_style(arcStyle);
lv.set_style_arc_color(arcStyle, lv.lv_palette_main(lv.LV_PALETTE_BLUE));
lv.set_style_arc_width(arcStyle, 8);
lv.lv_obj_add_style(arc, arcStyle, 0);
```

### **Bar (نوار پیشرفت)**

```javascript
// ایجاد bar
let bar = lv.lv_bar_create(screen);
lv.lv_obj_set_size(bar, 200, 20);
lv.lv_obj_set_pos(bar, 20, 120);

// تنظیم محدوده و مقدار
lv.lv_bar_set_range(bar, 0, 100);
lv.lv_bar_set_value(bar, 60, lv.LV_ANIM_ON);

// استایل bar
let barStyle = lv.lv_style_create();
lv.init_style(barStyle);
lv.set_style_bg_color(barStyle, lv.lv_palette_main(lv.LV_PALETTE_GREEN));
lv.set_style_bg_opa(barStyle, lv.LV_OPA_COVER);
lv.lv_obj_add_style(bar, barStyle, 0);
```

### **Roller (غلتک)**

```javascript
// ایجاد roller
let roller = lv.lv_roller_create(screen);
lv.lv_obj_set_pos(roller, 20, 300);
lv.lv_obj_set_size(roller, 100, 120);

// تنظیم گزینه‌ها
lv.lv_roller_set_options(roller, "January\nFebruary\nMarch\nApril\nMay\nJune\nJuly\nAugust\nSeptember\nOctober\nNovember\nDecember", lv.LV_ROLLER_MODE_NORMAL);

// تنظیم سطرهای قابل مشاهده
lv.lv_roller_set_visible_row_count(roller, 3);

// event برای انتخاب
lv.lv_obj_add_event_cb(roller, function(obj, event) {
    let selected = lv.lv_roller_get_selected(obj);
    let text = lv.lv_roller_get_options(obj).split('\n')[selected];
    console.log("Selected month:", text);
}, lv.LV_EVENT_VALUE_CHANGED);
```

### **Spinner (لودر چرخان)**

```javascript
// ایجاد spinner
let spinner = lv.lv_spinner_create(screen, 1000, 60);
lv.lv_obj_set_size(spinner, 50, 50);
lv.lv_obj_set_pos(spinner, 100, 100);

// استایل spinner
let spinnerStyle = lv.lv_style_create();
lv.init_style(spinnerStyle);
lv.set_style_arc_color(spinnerStyle, lv.lv_palette_main(lv.LV_PALETTE_BLUE));
lv.set_style_arc_width(spinnerStyle, 6);
lv.lv_obj_add_style(spinner, spinnerStyle, 0);
```

---

## 🎨 **مدیریت تصاویر با کش**

```javascript
// 🔥 سیستم کش تصاویر
let imgDesc = image.png_decode("images/logo.png"); // 🔥 کش خودکار
let img = lv.lv_img_create(screen);
lv.lv_img_set_src(img, imgDesc);
lv.lv_obj_set_pos(img, 50, 50);

// بررسی وجود فایل
if (image.file_exists("images/logo.png")) {
    console.log("File exists!");
}

// تنظیم pivot برای تصاویر
let pivot = [25, 25];
lv.lv_img_set_pivot(img, pivot);

// 🔥 تخریب تصویر وقتی نیاز نیست
image.png_destroy(imgDesc);

// 🔥 مدیریت کش تصاویر
let cacheInfo = image.get_cache_info();
console.log("Cache hits:", cacheInfo.hits, "Misses:", cacheInfo.misses);

// پاکسازی کش
image.clear_image_cache();
```

---

---



## 🎨 **مدیریت تصاویر**

### **نمایش تصاویر**

```javascript
// ایجاد آبجکت تصویر
let img = lv.lv_img_create(screen);
lv.lv_obj_set_pos(img, 50, 50);

// تنظیم منبع تصویر (از SPIFFS)
lv.lv_img_set_src(img, "A:/images/logo.png");

// تنظیم opacity
lv.lv_obj_set_style_img_opa(img, lv.LV_OPA_70, 0);
```

### **ترنسفورمیشن تصاویر**

```javascript
// چرخش تصویر
lv.lv_img_set_angle(img, 45); // 45 درجه

// زوم
lv.lv_img_set_zoom(img, 256); // 100% (256 = 1.0)

// جابجایی
lv.lv_img_set_offset_x(img, 10);
lv.lv_img_set_offset_y(img, -5);
```

---

## 🏗️ **Layout و Flexbox**

### **Flex Layout**

```javascript
// تنظیم flex flow
lv.lv_obj_set_flex_flow(parent, lv.LV_FLEX_FLOW_ROW_WRAP);

// تنظیم alignment
lv.lv_obj_set_style_flex_main_place(parent, lv.LV_FLEX_ALIGN_SPACE_EVENLY, 0);
lv.lv_obj_set_style_flex_cross_place(parent, lv.LV_FLEX_ALIGN_CENTER, 0);

// تنظیم grow برای آبجکت‌ها
lv.lv_obj_set_flex_grow(child1, 1);
lv.lv_obj_set_flex_grow(child2, 2); // دو برابر child1
```

### **انواع Flex Flow**

```javascript
lv.LV_FLEX_FLOW_ROW                 // ردیف
lv.LV_FLEX_FLOW_COLUMN             // ستون
lv.LV_FLEX_FLOW_ROW_WRAP           // ردیف با wrap
lv.LV_FLEX_FLOW_COLUMN_WRAP        // ستون با wrap
lv.LV_FLEX_FLOW_ROW_REVERSE        // ردیف معکوس
```

---

## ⚡ **مدیریت State و Flags**

### **مدیریت State**

```javascript
// اضافه کردن state
lv.lv_obj_add_state(obj, lv.LV_STATE_CHECKED);
lv.lv_obj_add_state(obj, lv.LV_STATE_DISABLED);

// حذف state
lv.lv_obj_clear_state(obj, lv.LV_STATE_DISABLED);

// بررسی state
let isChecked = lv.lv_obj_has_state(obj, lv.LV_STATE_CHECKED);
```

### **مدیریت Flags**

```javascript
// اضافه کردن flag
lv.lv_obj_add_flag(obj, lv.LV_OBJ_FLAG_CLICKABLE);
lv.lv_obj_add_flag(obj, lv.LV_OBJ_FLAG_SCROLLABLE);

// حذف flag
lv.lv_obj_clear_flag(obj, lv.LV_OBJ_FLAG_SCROLLABLE);

// بررسی flag
let isClickable = lv.lv_obj_has_flag(obj, lv.LV_OBJ_FLAG_CLICKABLE);
```


---

## ⏰ **مدیریت تایمرها (جدید)**

### **تایمرهای setTimeout/setInterval**

```javascript
// 🔥 setTimeout با مدیریت حافظه
let timer1 = setTimeout(function() {
    console.log("Timeout executed!");
}, 1000);

// 🔥 setInterval
let timer2 = setInterval(function() {
    console.log("Interval tick!");
}, 2000);

// 🔥 حذف تایمرها
clearTimeout(timer1);
clearInterval(timer2);
```
## 🎯 **مدیریت موقعیت و Alignment**

### **تراز کردن آبجکت‌ها**

```javascript
// تراز مرکزی
lv.lv_obj_center(obj);

// تراز نسبی
lv.lv_obj_align(obj, lv.LV_ALIGN_TOP_LEFT, 10, 10);
lv.lv_obj_align(obj, lv.LV_ALIGN_BOTTOM_RIGHT, -10, -10);

// تراز نسبت به آبجکت دیگر
let parent = lv.lv_obj_create(screen);
let child = lv.lv_obj_create(parent);
lv.lv_obj_align_to(child, parent, lv.LV_ALIGN_CENTER, 0, 0);
```

### **ثابت‌های Alignment**

```javascript
// انواع تراز
lv.LV_ALIGN_TOP_LEFT
lv.LV_ALIGN_TOP_MID
lv.LV_ALIGN_TOP_RIGHT
lv.LV_ALIGN_BOTTOM_LEFT
lv.LV_ALIGN_BOTTOM_MID
lv.LV_ALIGN_BOTTOM_RIGHT
lv.LV_ALIGN_LEFT_MID
lv.LV_ALIGN_RIGHT_MID
lv.LV_ALIGN_CENTER
```

---

## 🔄 **انیمیشن و Effects**

### **انیمیشن‌های ساده**

```javascript
// fade in
lv.lv_obj_fade_in(obj, 1000, 0); // 1000ms delay

// fade out
lv.lv_obj_fade_out(obj, 1000, 0);

// حذف تمام انیمیشن‌ها
lv.lv_anim_del_all();
```

### **ترنسفورمیشن‌ها**

```javascript
// چرخش
lv.lv_style_set_transform_angle(style, 45); // 45 درجه

// مقیاس
lv.lv_style_set_transform_zoom(style, 1.5); // 150%

// موقعیت
lv.lv_style_set_translate_x(style, 10);
lv.lv_style_set_translate_y(style, -5);
```

---

---

## 🎮 **مدیریت رویدادها با مدیریت حافظه**

### **ثبت event handler ایمن**

```javascript
// 🔥 ثبت event با مدیریت حافظه
lv.lv_obj_add_event_cb(btn, function(obj, event) {
    console.log("Event:", event);
    console.log("Position:", lv.indev_get_x(), lv.indev_get_y()); // 🔥 توابع جدید
}, lv.LV_EVENT_CLICKED);

// 🔥 حذف event
lv.lv_obj_remove_event_cb(btn);

// 🔥 حذف تمام eventهای یک آبجکت
lv.lv_obj_remove_all_event_cb(btn);

// 🔥 گرفتن اطلاعات eventهای فعال
let eventInfo = lv.get_active_events_info();
console.log("Active events:", eventInfo.count);
```

### **انواع رویدادها**

```javascript
lv.LV_EVENT_PRESSED
lv.LV_EVENT_RELEASED
lv.LV_EVENT_CLICKED
lv.LV_EVENT_VALUE_CHANGED
lv.LV_EVENT_FOCUSED
lv.LV_EVENT_DEFOCUSED
```

---

## 📱 **مدیریت صفحه نمایش**

### **اطلاعات صفحه نمایش**

```javascript
// 🔥 توابع جدید برای اندازه صفحه
let screenWidth = lv.get_screen_width();
let screenHeight = lv.get_screen_height();
console.log("Screen size:", screenWidth, "x", screenHeight);

// 🔥 چرخش صفحه نمایش
lv.disp_set_rotation(0); // 0-3 (0°, 90°, 180°, 270°)
```

### **موقعیت‌یابی پیشرفته**

```javascript
// 🔥 گرفتن موقعیت مطلق
let absX = lv.lv_obj_get_abs_x(obj);
let absY = lv.lv_obj_get_abs_y(obj);

// تنظیم pivot برای تصاویر
let pivot = [50, 50];
lv.lv_img_set_pivot(img, pivot);
```

---

## 🎯 **مثال کامل با مدیریت حافظه**

### **برنامه نمونه - کنترل پنل با مدیریت حافظه**

```javascript
class UIController {
    constructor() {
        this.screen = lv.lv_scr_act();
        this.objects = [];
        this.styles = [];
        this.initUI();
    }

    initUI() {
        // ایجاد دکمه‌ها
        this.createButton("Start", 50, 30, this.onButtonClick.bind(this));
        this.createButton("Stop", 180, 30, this.onButtonClick.bind(this));
        
        // ایجاد اسلایدر
        this.createSlider(20, 100, this.onSliderChange.bind(this));
        
        // ایجاد سوییچ
        this.createSwitch(20, 150, this.onSwitchChange.bind(this));
        
        // ایجاد چک‌باکس
        this.createCheckbox(20, 200, "Enable Feature", this.onCheckboxChange.bind(this));
    }

    createButton(text, x, y, callback) {
        let style = lv.lv_style_create();
        lv.init_style(style);
        lv.set_style_bg_color(style, lv.lv_palette_main(lv.LV_PALETTE_BLUE));
        lv.set_style_radius(style, 10);

        let btn = lv.lv_btn_create(this.screen);
        lv.lv_obj_set_size(btn, 120, 50);
        lv.lv_obj_set_pos(btn, x, y);
        lv.lv_obj_add_style(btn, style, 0);

        let label = lv.lv_label_create(btn);
        lv.lv_label_set_text(label, text);
        lv.lv_obj_center(label);

        // ثبت event
        lv.lv_obj_add_event_cb(btn, callback, lv.LV_EVENT_CLICKED);

        this.objects.push(btn);
        this.styles.push(style);

        return { obj: btn, style: style };
    }

    createSlider(x, y, callback) {
        let slider = lv.lv_slider_create(this.screen);
        lv.lv_obj_set_size(slider, 200, 20);
        lv.lv_obj_set_pos(slider, x, y);
        lv.lv_slider_set_range(slider, 0, 100);
        lv.lv_slider_set_value(slider, 50, lv.LV_ANIM_OFF);

        lv.lv_obj_add_event_cb(slider, callback, lv.LV_EVENT_VALUE_CHANGED);
        this.objects.push(slider);

        return slider;
    }

    createSwitch(x, y, callback) {
        let sw = lv.lv_switch_create(this.screen);
        lv.lv_obj_set_pos(sw, x, y);
        lv.lv_obj_add_event_cb(sw, callback, lv.LV_EVENT_VALUE_CHANGED);
        this.objects.push(sw);
        return sw;
    }

    createCheckbox(x, y, text, callback) {
        let cb = lv.lv_checkbox_create(this.screen);
        lv.lv_obj_set_pos(cb, x, y);
        lv.lv_checkbox_set_text(cb, text);
        lv.lv_obj_add_event_cb(cb, callback, lv.LV_EVENT_VALUE_CHANGED);
        this.objects.push(cb);
        return cb;
    }

    // Event handlers
    onButtonClick(obj, event) {
        let text = lv.lv_label_get_text(lv.lv_obj_get_child(obj, 0));
        console.log("Button clicked:", text);
    }

    onSliderChange(obj, event) {
        let value = lv.lv_slider_get_value(obj);
        console.log("Slider value:", value);
    }

    onSwitchChange(obj, event) {
        let isOn = lv.lv_obj_has_state(obj, lv.LV_STATE_CHECKED);
        console.log("Switch is:", isOn ? "ON" : "OFF");
    }

    onCheckboxChange(obj, event) {
        let isChecked = lv.lv_obj_has_state(obj, lv.LV_STATE_CHECKED);
        console.log("Checkbox is:", isChecked ? "checked" : "unchecked");
    }

    destroyAll() {
        // 🔥 تخریب تمام آبجکت‌ها به صورت ایمن
        this.objects.forEach((obj, index) => {
            if (this.styles[index]) {
                lv.destroy_obj({
                    nativePtr: obj,
                    stylePtr: this.styles[index]
                });
            } else {
                lv.lv_obj_del(obj);
            }
        });

        this.objects = [];
        this.styles = [];

        // 🔥 پاکسازی باقی‌مانده‌ها
        let count = lv.safe_destroy_all();
        console.log("Total destroyed:", count);
    }
}

// استفاده از کلاس
let ui = new UIController();

// وقتی برنامه تمام شد:
// ui.destroyAll();
```

---

## 🔧 **الگوهای مدیریت حافظه**

### **الگوی ۱: مدیریت دستی**

```javascript
function createTemporaryUI() {
    let tempObj = lv.lv_obj_create(screen);
    let tempStyle = lv.lv_style_create();
    lv.init_style(tempStyle);
    
    // استفاده از آبجکت
    
    // 🔥 تخریب وقتی کار تمام شد
    return function cleanup() {
        lv.destroy_obj({
            nativePtr: tempObj,
            stylePtr: tempStyle
        });
    };
}

let cleanup = createTemporaryUI();
// بعد از استفاده:
cleanup();
```

### **الگوی ۲: مدیریت خودکار با کلاس**

```javascript
class ManagedObject {
    constructor(parent) {
        this.obj = lv.lv_obj_create(parent);
        this.style = lv.lv_style_create();
        lv.init_style(this.style);
        lv.lv_obj_add_style(this.obj, this.style, 0);
    }

    destroy() {
        lv.destroy_obj({
            nativePtr: this.obj,
            stylePtr: this.style
        });
        this.obj = null;
        this.style = null;
    }

    // وقتی آبجکت از scope خارج می‌شود
    __destruct() {
        if (this.obj) this.destroy();
    }
}
```

---

## 🚨 **نکات مهم مدیریت حافظه**

### **کارهای ضروری**

```javascript
// ✅ همیشه استایل‌ها را مقداردهی اولیه کنید
lv.init_style(style);

// ✅ همیشه از destroy_obj استفاده کنید
lv.destroy_obj({ nativePtr: obj, stylePtr: style });

// ✅ eventها را حذف کنید وقتی نیاز نیستند
lv.lv_obj_remove_event_cb(obj);

// ✅ تایمرها را حذف کنید
clearTimeout(timer);
```

### **کارهای ممنوع**

```javascript
// ❌ هرگز مستقیماً حافظه را آزاد نکنید
// lv_mem_free(obj); // اشتباه!

// ❌ آبجکت‌ها را بدون حذف event رها نکنید

// ❌ استایل‌های استفاده شده را مستقیماً حذف نکنید
```

### **بررسی سلامت حافظه**

```javascript
// بررسی وضعیت کش تصاویر
let cacheInfo = image.get_cache_info();
console.log("Image cache:", cacheInfo);

// بررسی eventهای فعال
let eventInfo = lv.get_active_events_info();
console.log("Active events:", eventInfo.count);

// بررسی valid بودن آبجکت‌ها
if (lv.lv_obj_is_valid(obj)) {
    console.log("Object is healthy");
}
```

---

## 📊 **ثابت‌های جدید**

### **مدیریت حافظه**

```javascript
// ماکزیمم سایز کش تصاویر
image.MAX_CACHE_SIZE = 10;

// انواع فونت‌های قابل انتخاب
lv.lvgl_style_get_font(8);   // فونت 8px
lv.lvgl_style_get_font(12);  // فونت 12px  
lv.lvgl_style_get_font(16);  // فونت 16px
lv.lvgl_style_get_font(20);  // فونت 20px (پیش‌فرض)
lv.lvgl_style_get_font(24);  // فونت 24px
```
## 🔧 **نکات مهم و بهترین روش‌ها**


```javascript
// پاک‌سازی استایل‌ها وقتی استفاده نمی‌شوند
// lv.lv_style_reset(style); // در LVGL 8.3+

// استفاده از استایل‌های مشترک برای آبجکت‌های مشابه
```

### **بهینه‌سازی عملکرد**

```javascript
// غیرفعال کردن scroll برای آبجکت‌های ساده
lv.lv_obj_clear_flag(obj, lv.LV_OBJ_FLAG_SCROLLABLE);

// استفاده از انیمیشن فقط وقتی لازم است
lv.lv_slider_set_value(slider, 75, lv.LV_ANIM_OFF); // بدون انیمیشن
```

### **عیب‌یابی**

```javascript
// بررسی visibility
let isVisible = lv.lv_obj_is_visible(obj);

// بررسی موقعیت و سایز
let x = lv.lv_obj_get_x(obj);
let y = lv.lv_obj_get_y(obj);
let width = lv.lv_obj_get_width(obj);
let height = lv.lv_obj_get_height(obj);
```

---

## 🎨 **پالت رنگ‌های کامل**

```javascript
// تمام پالت‌های رنگی موجود
lv.LV_PALETTE_RED
lv.LV_PALETTE_PINK
lv.LV_PALETTE_PURPLE
lv.LV_PALETTE_DEEP_PURPLE
lv.LV_PALETTE_INDIGO
lv.LV_PALETTE_BLUE
lv.LV_PALETTE_LIGHT_BLUE
lv.LV_PALETTE_CYAN
lv.LV_PALETTE_TEAL
lv.LV_PALETTE_GREEN
lv.LV_PALETTE_LIGHT_GREEN
lv.LV_PALETTE_LIME
lv.LV_PALETTE_YELLOW
lv.LV_PALETTE_AMBER
lv.LV_PALETTE_ORANGE
lv.LV_PALETTE_DEEP_ORANGE
lv.LV_PALETTE_BROWN
lv.LV_PALETTE_BLUE_GREY
lv.LV_PALETTE_GREY
```



## 🏗️ ساختار ماژول

### 1. **توابع مدیریت استایل**
### 2. **توابع مدیریت آبجکت**
### 3. **توابع کمکی و ابزار**

## 🎨 بخش 1: مدیریت استایل‌ها

### 🔸 ایجاد و تخریب استایل

```javascript
// 1. ایجاد استایل جدید
var myStyle = styleModule.lv_style_create();
print("استایل ایجاد شد: " + myStyle);

// 2. تنظیم خصوصیات استایل
styleModule.set_style_bg_color(myStyle, 0x000033);  // رنگ پس‌زمینه آبی تیره
styleModule.set_style_bg_opa(myStyle, 255);         // شفافیت کامل
styleModule.set_style_radius(myStyle, 15);          // گوشه‌های گرد

// 3. تخریب استایل (وقتی دیگر نیاز نیست)
styleModule.lv_style_destroy(myStyle);
print("استایل حذف شد");
```

### 🎨 رنگ‌ها و شفافیت

| تابع | پارامترها | مثال | توضیح |
|------|-----------|------|-------|
| `set_style_bg_color` | `(style, color)` | `set_style_bg_color(style, 0xFF0000)` | رنگ پس‌زمینه (هگزادسیمال) |
| `set_style_bg_opa` | `(style, opacity)` | `set_style_bg_opa(style, 128)` | شفافیت (0-255) |
| `set_style_text_color` | `(style, color)` | `set_style_text_color(style, 0x00FF00)` | رنگ متن |
| `set_style_border_color` | `(style, color)` | `set_style_border_color(style, 0xFFFFFF)` | رنگ حاشیه |

### 📏 اندازه‌ها و موقعیت

```javascript
// تنظیم ابعاد
styleModule.set_style_width(myStyle, 100);      // عرض 100 پیکسل
styleModule.set_style_height(myStyle, 50);      // ارتفاع 50 پیکسل

// تنظیم موقعیت
styleModule.set_style_x(myStyle, 20);          // موقعیت X
styleModule.set_style_y(myStyle, 30);          // موقعیت Y

// Padding
styleModule.set_style_pad_all(myStyle, 10);    // Padding همه جهات
styleModule.set_style_pad_top(myStyle, 5);     // Padding بالا
```

### 🖋️ متن و فونت

```javascript
// تنظیم فونت
styleModule.set_style_text_font(myStyle, lv.lv_font_default());

// فاصله متن
styleModule.set_style_text_letter_space(myStyle, 2);  // فاصله حروف
styleModule.set_style_text_line_space(myStyle, 5);    // فاصله خطوط

// تراز متن
styleModule.set_style_text_align(myStyle, lv.LV_TEXT_ALIGN_CENTER);
```

### ⭕ استایل‌های آرک (Arc)

```javascript
// تنظیمات آرک
styleModule.set_style_arc_width(myStyle, 8);           // عرض خط آرک
styleModule.set_style_arc_color(myStyle, 0xFF5555);    // رنگ آرک
styleModule.set_style_arc_indic_width(myStyle, 6);     // عرض نشانگر آرک
styleModule.set_style_arc_indic_color(myStyle, 0x00FF00); // رنگ نشانگر

// مخفی کردن knob (مرکز آرک)
styleModule.lv_arc_hide_knob(arcObject);
```

## 🗑️ بخش 2: مدیریت آبجکت و حافظه

### 🔥 حذف ایمن آبجکت‌ها

```javascript
// روش صحیح مدیریت چرخه عمر آبجکت
var obj = lv.lv_obj_create(screen);
var style = styleModule.lv_style_create();

// 1. تنظیم استایل
styleModule.set_style_bg_color(style, 0x0000FF);
lv.lv_obj_add_style(obj, style, 0);

// 2. حذف آبجکت (هنگام خروج)
styleModule.lv_obj_del(obj);

// 3. حذف استایل
styleModule.lv_style_destroy(style);

print("آبجکت و استایل با موفقیت حذف شدند");
```

### 🧹 پاکسازی گروهی

```javascript
// حذف تمام فرزندان یک آبجکت
var parent = lv.lv_obj_create(screen);

// ایجاد چند فرزند
var child1 = lv.lv_obj_create(parent);
var child2 = lv.lv_obj_create(parent);

// حذف همه فرزندان
styleModule.lv_obj_delete_all_children(parent);
print("تمام فرزندان حذف شدند");

// پاکسازی کامل صفحه
styleModule.lv_obj_clean(screen);
```

### 🔄 مدیریت استایل روی آبجکت

```javascript
// حذف یک استایل خاص از آبجکت
styleModule.lv_obj_remove_style(obj, myStyle, 0);

// حذف تمام استایل‌های آبجکت
styleModule.lv_obj_remove_style_all(obj);

// ریست استایل به حالت پیش‌فرض
styleModule.lv_style_reset(myStyle);
```

## ⚙️ بخش 3: توابع کمکی

### 🎨 تبدیل رنگ

```javascript
// استفاده از رنگ‌های LVGL
var colorRed = lv.lv_color_hex(0xFF0000);
var colorGreen = lv.lv_color_hex(0x00FF00);
var colorBlue = lv.lv_color_hex(0x0000FF);

// در استایل
styleModule.set_style_bg_color(myStyle, colorRed);
```

### 📊 وضعیت سیستم

```javascript
// بررسی وضعیت ماژول
print("ماژول استایل فعال است");

// نمونه استفاده در حلقه اصلی
while (true) {
    // کار با استایل‌ها
    Timer.delay(1000);
    
    if (GPIO.readButton(GPIO.Buttons.BACK)) {
        // پاکسازی قبل از خروج
        styleModule.lv_obj_clean(lv.lv_scr_act());
        break;
    }
}
```

## 📋 جدول توابع اصلی

### 🎨 استایل‌های گرافیکی
| تابع | کاربرد | مقادیر نمونه |
|------|--------|--------------|
| `set_style_bg_color` | رنگ پس‌زمینه | `0xFF0000` (قرمز) |
| `set_style_border_width` | عرض حاشیه | `1`, `2`, `3` |
| `set_style_radius` | گردی گوشه | `0` (مربع), `10` (گرد) |
| `set_style_shadow_width` | عرض سایه | `5`, `10` |

### 📏 استایل‌های ابعادی
| تابع | کاربرد | واحد |
|------|--------|------|
| `set_style_width` | عرض | پیکسل |
| `set_style_height` | ارتفاع | پیکسل |
| `set_style_pad_all` | padding | پیکسل |
| `set_style_arc_width` | عرض آرک | پیکسل |

### 🖋️ استایل‌های متن
| تابع | کاربرد | گزینه‌ها |
|------|--------|----------|
| `set_style_text_color` | رنگ متن | کد هگز |
| `set_style_text_font` | فونت | اشاره‌گر فونت |
| `set_style_text_align` | تراز متن | `LEFT`, `CENTER`, `RIGHT` |

## 🛠️ نمونه کد کامل

```javascript
print("=== نمونه ایجاد رابط کاربری با استایل ===");

var lv = require('@native.lvgl');
var styleModule = require('@native.lv_style');

// 1. ایجاد صفحه
var scr = lv.lv_scr_act();

// 2. ایجاد استایل اصلی
var mainStyle = styleModule.lv_style_create();
styleModule.set_style_bg_color(mainStyle, 0x000033);
styleModule.set_style_bg_opa(mainStyle, 255);
styleModule.set_style_radius(mainStyle, 15);

// 3. ایجاد استایل متن
var textStyle = styleModule.lv_style_create();
styleModule.set_style_text_color(textStyle, 0x00FFFF);
styleModule.set_style_text_font(textStyle, lv.lv_font_default());

// 4. ایجاد کانتینر
var container = lv.lv_obj_create(scr);
lv.lv_obj_set_size(container, 150, 100);
lv.lv_obj_center(container);
lv.lv_obj_add_style(container, mainStyle, 0);

// 5. ایجاد برچسب
var label = lv.lv_label_create(container);
lv.lv_label_set_text(label, "سلام دنیا!");
lv.lv_obj_add_style(label, textStyle, 0);
lv.lv_obj_center(label);

print("✅ رابط کاربری ایجاد شد");

// 6. مدیریت حافظه (هنگام خروج)
function cleanup() {
    print("پاکسازی حافظه...");
    styleModule.lv_obj_del(container);
    styleModule.lv_style_destroy(mainStyle);
    styleModule.lv_style_destroy(textStyle);
    print("پاکسازی کامل");
}

// خروج با دکمه BACK
while (true) {
    if (GPIO.readButton(GPIO.Buttons.BACK)) {
        cleanup();
        break;
    }
    Timer.delay(100);
}
```

## ⚠️ بهترین روش‌ها (Best Practices)

### ✅ کارهای درست
```javascript
// 1. همیشه استایل‌ها را بعد از استفاده حذف کنید
var style = styleModule.lv_style_create();
// ... استفاده از استایل
styleModule.lv_style_destroy(style);

// 2. آبجکت‌های فرزند را قبل از والد حذف کنید
styleModule.lv_obj_delete_all_children(parent);
styleModule.lv_obj_del(parent);

// 3. از رنگ‌های هگزادسیمال استفاده کنید
styleModule.set_style_bg_color(style, 0xRRGGBB);
```

### ❌ کارهای نادرست
```javascript
// 1. فراموش کردن حذف استایل (نشتی حافظه)
var style = styleModule.lv_style_create();
// استفاده بدون حذف ← نشتی حافظه!

// 2. حذف والد قبل از فرزندان
styleModule.lv_obj_del(parent); // خطا! فرزندان هنوز وجود دارند
styleModule.lv_obj_delete_all_children(parent); // باید اول این کار شود

// 3. استفاده همزمان از چند استایل متناقض
styleModule.set_style_width(style, 100);
styleModule.set_style_width(style, 200); // مقدار قبلی بازنویسی می‌شود
```

## 🔍 عیب‌یابی (Troubleshooting)

| مشکل | علت احتمالی | راه حل |
|------|-------------|--------|
| خطای `not a function` | ماژول بارگذاری نشده | `require('@native.lv_style')` بررسی کنید |
| آبجکت حذف نمی‌شود | فرزندان فعال دارند | اول `lv_obj_delete_all_children` استفاده کنید |
| رنگ نمایش نمی‌شود | مقدار شفافیت صفر است | `set_style_bg_opa(style, 255)` تنظیم کنید |
| گوشه‌ها گرد نمی‌شوند | مقدار radius کوچک است | مقادیر بزرگتر (10+) امتحان کنید |

## 📚 مرجع سریع

```javascript
// ایجاد و حذف
var style = styleModule.lv_style_create();
styleModule.lv_style_destroy(style);

// رنگ‌ها
styleModule.set_style_bg_color(style, 0x000033);
styleModule.set_style_text_color(style, 0xFFFFFF);

// ابعاد
styleModule.set_style_width(style, 100);
styleModule.set_style_height(style, 50);
styleModule.set_style_radius(style, 10);

// حذف
styleModule.lv_obj_del(obj);
styleModule.lv_obj_delete_all_children(parent);
```

این راهنما تمام قابلیت‌های ماژول استایل LVGL شما را پوشش می‌دهد و برای توسعه‌دهندگان تازه‌کار و حرفه‌ای مفید است.

---
این راهنمای کامل تمام ویجت‌های اصلی LVGL را همراه با مدیریت حافظه پیشرفته پوشش می‌دهد و بهترین روش‌ها برای ایجاد رابط‌های کاربری پایدار و بدون memory leak را ارائه می‌کند.







# 📚 **راهنمای کامل ماژول‌های EVM برای ESP32**

## 🎯 **فهرست ماژول‌ها**

### **۱. ماژول Console (کنترل خروجی)**
### **۲. ماژول FileSystem (مدیریت فایل)**
### **۳. ماژول GPIO (کنترل سخت‌افزار)**
### **۴. ماژول Process (اطلاعات سیستم)**
### **۵. ماژول Timer (تایمر و زمان)**
### **۶. ماژول WiFi (شبکه)**
### **۷. ماژول ADC (مبدل آنالوگ به دیجیتال)**
### **۸. ماژول PWM (مدولاسیون عرض پالس)**
### **۹. ماژول I2C (ارتباط I2C)**
### **۱۰. ماژول SPI (ارتباط SPI)**
### **۱۱. ماژول UART (ارتباط سریال)**
### **۱۲. ماژول Touch (سنسور لمسی)**
### **۱۳. ماژول DAC (مبدل دیجیتال به آنالوگ)**
### **۱۴. ماژول DMA (دسترسی مستقیم به حافظه)**
### **۱۵. ماژول Mongoose (شبکه)**
### **۱۶. ماژول MQTT (پروتکل MQTT)**
### **۱۷. ماژول FTP (انتقال فایل)**
### **۱۸. ماژول LVGL (رابط کاربری گرافیکی)**

---

## ۱. 🖥️ **ماژول Console**

### **توابع اصلی**
```javascript
// چاپ اطلاعات
console.log("Hello World");
console.info("Information message");
console.warn("Warning message");
console.error("Error message");

// دیباگ (فقط در حالت دیباگ)
console.debug("Debug message");

// مدیریت کنسول
console.clear();          // پاک کردن کنسول
console.trace();          // نمایش stack trace

// تایمر
console.time("label");    // شروع تایمر
console.timeEnd("label"); // پایان تایمر

// چاپ بدون خط جدید
console.write("text");
```

### **مثال کاربردی**
```javascript
console.log("🚀 Starting application...");
console.time("appStart");

// کد برنامه
for(let i = 0; i < 5; i++) {
    console.log(`Counter: ${i}`);
}

console.timeEnd("appStart");
console.info("✅ Application started successfully");
```

---

## ۲. 📁 **ماژول FileSystem**

### **توابع اصلی**
```javascript
// خواندن/نوشتن فایل
let content = fs.readFileSync("/sdcard/file.txt");
fs.writeFileSync("/sdcard/file.txt", "Hello World");

// مدیریت دایرکتوری
let files = fs.readdirSync("/sdcard");
fs.mkdir("/sdcard/newfolder");
fs.rmdir("/sdcard/folder");

// اطلاعات فایل
let stats = fs.statSync("/sdcard/file.txt");
console.log(`Size: ${stats.size} bytes`);

// بررسی وجود فایل
if (fs.existsSync("/sdcard/file.txt")) {
    console.log("File exists");
}

// حذف فایل
fs.unlink("/sdcard/oldfile.txt");

// مدیریت استوریج
fs.writeFile("/config.json", '{"name":"test"}', fs.SPIFFS);
fs.copyFile("/spiffs/config.json", "/sdcard/backup.json", fs.SPIFFS, fs.SDCARD);


// 📘 راهنمای استفاده از fs.readFile (نسخه ساده)

// ========================
// 🎯 فرمت‌های معتبر:
// ========================

// 1️⃣ خواندن با auto-detection
//    (اول SD Card، سپس SPIFFS)
const data1 = fs.readFile("/apps/config.json");

// 2️⃣ خواندن از storage مشخص
//    از SD Card بخوان
const data2 = fs.readFile("/apps/config.json", fs.SDCARD);

//    از SPIFFS بخوان
const data3 = fs.readFile("/apps/config.json", fs.SPIFFS);

```

### **مثال کاربردی**
```javascript
// ذخیره داده سنسور
let sensorData = {
    temperature: 25.5,
    humidity: 60,
    timestamp: Date.now()
};

fs.writeFileSync("/sdcard/sensor_data.json", JSON.stringify(sensorData));

// خواندن داده
let data = JSON.parse(fs.readFileSync("/sdcard/sensor_data.json"));
console.log(`Temperature: ${data.temperature}°C`);
```

---

## ۳. 🔌 **ماژول GPIO**

### **توابع اصلی**
```javascript
// روش ساده
gpio.read(12);
gpio.write(12, 1);
gpio.setDirection(12, gpio.OUTPUT);

// روش شی‌گرا
let led = GPIO.create(12, GPIO.Direction.OUT);
led.writeSync(1);

// خواندن دکمه‌ها
let buttonState = gpio.readButton(gpio.BUTTON_UP);

// پین‌های مجاز
let availablePins = gpio.getAvailablePins();
```

### **ثابت‌ها**
```javascript
// جهت
gpio.INPUT = 0
gpio.OUTPUT = 1

// سطح
gpio.LOW = 0
gpio.HIGH = 1

// دکمه‌ها
gpio.BUTTON_UP = 0
gpio.BUTTON_SELECT = 1
gpio.BUTTON_DOWN = 2
gpio.BUTTON_BACK = 3
```

### **مثال کاربردی**
```javascript
// کنترل LED
const LED_PIN = 2;
gpio.setDirection(LED_PIN, gpio.OUTPUT);

// چشمک زدن
let counter = 0;
setInterval(() => {
    let state = counter % 2;
    gpio.write(LED_PIN, state);
    console.log(`LED ${state ? 'ON' : 'OFF'}`);
    counter++;
}, 1000);

// خواندن دکمه
setInterval(() => {
    let upBtn = gpio.readButton(gpio.BUTTON_UP);
    if (upBtn) {
        console.log("UP button pressed");
    }
}, 100);
```

---

## ۴. ⚙️ **ماژول Process**

### **توابع اصلی**
```javascript
// اطلاعات حافظه
let mem = process.memoryUsage();
console.log(`Memory: ${mem.usage.toFixed(1)}%`);

// زمان فعالیت
let uptime = process.uptime();
console.log(`Uptime: ${uptime} seconds`);

// استفاده CPU
let cpu = process.cpuUsage();
console.log(`CPU: ${cpu.total.toFixed(1)}%`);

// اطلاعات سیستم
console.log(`Arch: ${process.arch}`);        // "esp32"
console.log(`Platform: ${process.platform}`); // "esp32"
console.log(`PID: ${process.pid}`);          // ID پردازش

// مدیریت پردازش
process.exit(0);        // خروج
process.kill();         // پایان پردازش

// آمار حافظه
let heap = process.heapStats();
console.log(`Free heap: ${heap.free} bytes`);
```

### **مثال کاربردی**
```javascript
// مانیتورینگ سیستم
setInterval(() => {
    let mem = process.memoryUsage();
    let cpu = process.cpuUsage();
    let heap = process.heapStats();
    
    console.log("=== System Status ===");
    console.log(`Memory: ${mem.usage.toFixed(1)}%`);
    console.log(`CPU: ${cpu.total.toFixed(1)}%`);
    console.log(`Free Heap: ${(heap.free / 1024).toFixed(1)} KB`);
    console.log(`Uptime: ${process.uptime()}s`);
}, 5000);
```

---

## ۵. ⏰ **ماژول Timer**

### **توابع اصلی**
```javascript
// تأخیر
Timer.delay(1000);   // 1 ثانیه

// زمان سیستم
let currentTime = Timer.getTime(); // میلی‌ثانیه

// تایمرهای JavaScript
let timeoutId = Timer.setTimeout(() => {
    console.log("Timeout executed!");
}, 1000);

let intervalId = Timer.setInterval(() => {
    console.log("Interval executed!");
}, 2000);

// توقف تایمر
Timer.clearTimeout(timeoutId);
Timer.clearInterval(intervalId);

// زمان واقعی
Timer.setRealTime(10, 0, 0);   // ساعت 10:00:00
Timer.setTime(14, 30, 0);      // ساعت 14:30:00

// خواندن زمان
let time = Timer.getRealTime();
console.log(`Time: ${time.hours}:${time.minutes}:${time.seconds}`);

Timer.getTimeString();  // "14:30:00"
```

### **مثال کاربردی**
```javascript
// ساعت دیجیتال
setInterval(() => {
    let timeString = Timer.getTimeString();
    console.log(`🕒 ${timeString}`);
}, 1000);

// اجرای وظایف زمان‌بندی شده
Timer.setTimeout(() => {
    console.log("Task executed after 5 seconds");
}, 5000);

// تایمر تکراری برای خواندن سنسور
let sensorInterval = Timer.setInterval(() => {
    let value = ADC.read(ADC.CHANNEL_0);
    console.log(`Sensor value: ${value}`);
}, 2000);

// توقف بعد از 10 بار
let count = 0;
let stopInterval = Timer.setInterval(() => {
    count++;
    if (count >= 10) {
        Timer.clearInterval(sensorInterval);
        Timer.clearInterval(stopInterval);
        console.log("Sensor reading stopped");
    }
}, 2000);
```

---

## ۶. 📡 **ماژول WiFi**

### **توابع اصلی**
```javascript
// مقداردهی اولیه
WiFi.init();

// تنظیم حالت
WiFi.mode("sta");    // Station
WiFi.mode("ap");     // Access Point
WiFi.mode("both");   // هر دو

// اتصال به WiFi
WiFi.sta("MySSID", "MyPassword");

// ایجاد نقطه دسترسی
WiFi.ap("ESP32-AP", "12345678", 6);

// اسکن شبکه‌ها
let networks = WiFi.scan();

// وضعیت
let status = WiFi.status();
console.log(`STA: ${status.sta}, AP: ${status.ap}`);
console.log(`STA IP: ${status.staIP}, AP IP: ${status.apIP}`);

// آدرس IP
let staIP = WiFi.staIP();
let apIP = WiFi.apIP();

// اطلاعات کامل
let info = WiFi.info();

// مدیریت پیشرفته
WiFi.autoConnect();
WiFi.setAutoReconnect(true);
WiFi.maintain();
```

### **مثال کاربردی**
```javascript
// اتصال خودکار به WiFi
console.log("🔌 Connecting to WiFi...");

if (WiFi.init()) {
    WiFi.autoConnect();
    
    // بررسی وضعیت اتصال
    let connectCheck = setInterval(() => {
        let status = WiFi.status();
        
        if (status.sta) {
            console.log(`✅ Connected! IP: ${status.staIP}`);
            clearInterval(connectCheck);
            
            // شروع سرویس‌های شبکه
            startNetworkServices();
        } else {
            console.log("⏳ Connecting...");
        }
    }, 2000);
}

function startNetworkServices() {
    console.log("🚀 Starting network services...");
    
    // شروع سرور HTTP
    // شروع MQTT
    // شروع FTP
}
```

---

## ۷. 📊 **ماژول ADC**

### **توابع اصلی**
```javascript
// خواندن ولتاژ
let voltage = ADC.read(ADC.CHANNEL_0);

// خواندن مقدار خام
let rawValue = ADC.readRaw(ADC.CHANNEL_1);

// کانال‌های موجود
ADC.CHANNEL_0  // GPIO36
ADC.CHANNEL_1  // GPIO37
ADC.CHANNEL_2  // GPIO38
ADC.CHANNEL_3  // GPIO39
ADC.CHANNEL_4  // GPIO32
ADC.CHANNEL_5  // GPIO33
ADC.CHANNEL_6  // GPIO34
ADC.CHANNEL_7  // GPIO35
```

### **مثال کاربردی**
```javascript
// خواندن سنسور LDR (نور)
setInterval(() => {
    let lightValue = ADC.read(ADC.CHANNEL_0);
    console.log(`💡 Light level: ${lightValue.toFixed(2)}V`);
    
    if (lightValue < 1.0) {
        console.log("🌙 Dark environment");
    } else if (lightValue > 2.5) {
        console.log("☀️ Bright environment");
    }
}, 1000);

// خواندن پتانسیومتر
setInterval(() => {
    let potValue = ADC.read(ADC.CHANNEL_1);
    let percentage = (potValue / 3.3) * 100;
    console.log(`🎛️ Potentiometer: ${percentage.toFixed(1)}%`);
}, 500);
```

---

## ۸. 🎛️ **ماژول PWM**

### **توابع اصلی**
```javascript
// نوشتن PWM
PWM.write(12, 1000, 50);  // پین 12، فرکانس 1kHz، duty cycle 50%

// توقف PWM
PWM.stop(12);

// تنظیم فرکانس
PWM.setFrequency(12, 2000); // تغییر به 2kHz

// تنظیم duty cycle
PWM.setDutyCycle(12, 75); // تغییر به 75%
```

### **مثال کاربردی**
```javascript
// کنترل روشنایی LED
const LED_PIN = 2;
let brightness = 0;
let direction = 1;

setInterval(() => {
    PWM.write(LED_PIN, 1000, brightness);
    
    brightness += direction * 5;
    
    if (brightness >= 100 || brightness <= 0) {
        direction *= -1;
    }
    
    console.log(`💡 LED brightness: ${brightness}%`);
}, 50);

// کنترل سروو موتور
function setServoAngle(pin, angle) {
    // تبدیل زاویه به duty cycle (معمولاً 1ms تا 2ms)
    let dutyCycle = 5 + (angle / 180) * 10; // 5% to 15%
    PWM.write(pin, 50, dutyCycle); // فرکانس 50Hz برای سروو
}

// حرکت سروو از 0 تا 180 درجه
let servoAngle = 0;
setInterval(() => {
    setServoAngle(13, servoAngle);
    servoAngle = (servoAngle + 10) % 180;
}, 500);
```

---

## ۹. 🔄 **ماژول I2C**

### **توابع اصلی**
```javascript
// شروع I2C
I2C.begin(21, 22, 100000);  // SDA=21, SCL=22, فرکانس 100kHz

// نوشتن داده
I2C.write(0x68, 0x6B, 0x00);  // نوشتن روی آدرس 0x68، رجیستر 0x6B

// خواندن داده
let data = I2C.read(0x68, 0x3B);  // خواندن از آدرس 0x68، رجیستر 0x3B

// اسکن دستگاه‌ها
let devices = I2C.scan();
```

### **مثال کاربردی**
```javascript
// ارتباط با سنسور MPU6050
console.log("Initializing MPU6050...");

// شروع I2C
I2C.begin(21, 22, 400000); // SDA=21, SCL=22, 400kHz

// بیدار کردن MPU6050
I2C.write(0x68, 0x6B, 0x00);

// خواندن داده‌های شتاب‌سنج
setInterval(() => {
    let accelX = I2C.read16(0x68, 0x3B);
    let accelY = I2C.read16(0x68, 0x3D);
    let accelZ = I2C.read16(0x68, 0x3F);
    
    // تبدیل به g
    let gx = accelX / 16384.0;
    let gy = accelY / 16384.0;
    let gz = accelZ / 16384.0;
    
    console.log(`📊 Accelerometer - X: ${gx.toFixed(2)}g, Y: ${gy.toFixed(2)}g, Z: ${gz.toFixed(2)}g`);
}, 1000);
```

---

## ۱۰. 🔌 **ماژول SPI**

### **توابع اصلی**
```javascript
// شروع SPI
SPI.begin(23, 19, 18, 1000000);  // MOSI=23, MISO=19, SCLK=18, فرکانس 1MHz

// ارسال و دریافت داده
let received = SPI.transfer(0x55);  // ارسال 0x55 و دریافت داده

// فقط ارسال داده
SPI.write(0xAA);

// فقط دریافت داده
let data = SPI.read();

// تنظیم فرکانس
SPI.setFrequency(2000000); // 2MHz

// توقف SPI
SPI.end();
```

### **مثال کاربردی**
```javascript
// ارتباط با SD Card یا LCD
console.log("Initializing SPI...");

// شروع SPI
SPI.begin(23, 19, 18, 1000000); // MOSI=23, MISO=19, SCLK=18, 1MHz

// ارسال دستور به دستگاه
function sendCommand(cmd, data) {
    SPI.write(0x00); // شروع انتقال
    SPI.write(cmd);
    SPI.write(data);
    SPI.write(0xFF); // پایان انتقال
}

// خواندن از دستگاه
function readData() {
    SPI.write(0x01); // دستور خواندن
    let data1 = SPI.transfer(0x00);
    let data2 = SPI.transfer(0x00);
    return (data1 << 8) | data2;
}

// تست ارتباط
setInterval(() => {
    let data = readData();
    console.log(`📡 SPI Data: 0x${data.toString(16)}`);
}, 2000);
```

---

## ۱۱. 📡 **ماژول UART**

### **توابع اصلی**
```javascript
// شروع UART
UART.begin(115200, 1, 3);  // Baud=115200, TX=1, RX=3

// ارسال داده
UART.write("Hello ESP32!");
UART.write([0x48, 0x65, 0x6C, 0x6C, 0x6F]); // ارسال بایت‌آرایه

// بررسی داده موجود
if (UART.available() > 0) {
    let data = UART.read();
    console.log(`Received: ${data}`);
}

// خواندن رشته
let text = UART.readString();

// تنظیمات پیشرفته
UART.setTimeout(1000); // تایم‌اوت 1 ثانیه
```

### **مثال کاربردی**
```javascript
// ارتباط با GPS
console.log("Initializing GPS...");

// شروع UART برای GPS
UART.begin(9600, 17, 16); // TX=17, RX=16, 9600 baud

// خواندن داده‌های GPS
setInterval(() => {
    if (UART.available() > 0) {
        let gpsData = UART.readString();
        
        if (gpsData.startsWith("$GPGGA")) {
            // پردازش داده GPS
            let parts = gpsData.split(',');
            if (parts.length > 6 && parts[6] > 0) {
                let lat = parseFloat(parts[2]);
                let lon = parseFloat(parts[4]);
                console.log(`📍 GPS Location: ${lat}, ${lon}`);
            }
        }
    }
}, 1000);

// ارسال داده به دستگاه دیگر
setInterval(() => {
    let sensorData = `TEMP:${25.5},HUM:${60}`;
    UART.write(sensorData + '\n');
    console.log(`📤 Sent: ${sensorData}`);
}, 5000);
```

---

## ۱۲. 👆 **ماژول Touch**

 پین‌های تاچ ESP32 - لیست کامل:
پین‌های تاچ اصلی ESP32 (10 پین):
text

TOUCH_PAD_NUM0   -> GPIO4   ✅
TOUCH_PAD_NUM1   -> GPIO0   ⚠️ (پین boot - خطرناک!)
TOUCH_PAD_NUM2   -> GPIO2   ⚠️ (معمولاً LED داخلی)
TOUCH_PAD_NUM3   -> GPIO15  ✅
TOUCH_PAD_NUM4   -> GPIO13  ✅
TOUCH_PAD_NUM5   -> GPIO12  ✅
TOUCH_PAD_NUM6   -> GPIO14  ✅
TOUCH_PAD_NUM7   -> GPIO27  ✅
TOUCH_PAD_NUM8   -> GPIO33  ✅
TOUCH_PAD_NUM9   -> GPIO32  ✅

### **توابع اصلی**
```javascript
// خواندن مقدار تاچ
let value = Touch.read(Touch.PIN_0);

// خواندن تمام پین‌های کانفیگ شده
let allValues = Touch.readAll();

// آزادسازی پین
Touch.deinit(Touch.PIN_0);

// پین‌های موجود
Touch.PIN_0   // GPIO4
Touch.PIN_1   // GPIO0
Touch.PIN_2   // GPIO2
// ... تا 10 پین
```

### **مثال کاربردی**
```javascript
// تشخیص لمس
console.log("Initializing touch sensor...");

// خواندن پین تاچ
setInterval(() => {
    let touchValue = Touch.read(Touch.PIN_0);
    console.log(`👆 Touch value: ${touchValue}`);
    
    if (touchValue < 40) { // آستانه لمس
        console.log("✅ Touch detected!");
        
        // روشن کردن LED هنگام لمس
        gpio.write(2, gpio.HIGH);
        
        // خاموش کردن LED بعد از 200ms
        setTimeout(() => {
            gpio.write(2, gpio.LOW);
        }, 200);
    }
}, 100);

// استفاده از چندین پین تاچ
setInterval(() => {
    let touchData = Touch.readAll();
    console.log("Touch sensors:", touchData);
    
    for (let pin in touchData) {
        if (touchData[pin] < 40) {
            console.log(`Touch detected on pin ${pin}`);
        }
    }
}, 500);
```

---

## ۱۳. 🔊 **ماژول DAC**

### **توابع اصلی**
```javascript
// فعال‌سازی DAC
DAC.enable(DAC.CHANNEL_0);

// تولید سیگنال سینوسی
DAC.generateSine(DAC.CHANNEL_0, 1000, 2000); // 1kHz به مدت 2 ثانیه

// تنظیم ولتاژ خاص
DAC.writeVoltage(DAC.CHANNEL_0, 1.5); // 1.5 ولت

// تنظیم مقدار دیجیتال
DAC.write(DAC.CHANNEL_1, 128); // نیمه scale (1.65V)

// دریافت وضعیت
let status = DAC.getStatus();
```

### **مثال کاربردی**
```javascript
// تولید سیگنال تست
console.log("Starting DAC test...");

// فعال کردن DAC
DAC.enable(DAC.CHANNEL_0);
DAC.enable(DAC.CHANNEL_1);

// تولید سیگنال سینوسی 1kHz روی کانال 0
DAC.generateSine(DAC.CHANNEL_0, 1000, 5000); // 5 ثانیه

// تنظیم ولتاژ ثابت روی کانال 1
DAC.writeVoltage(DAC.CHANNEL_1, 1.2);

// تغییر ولتاژ هر 2 ثانیه
let voltage = 0.5;
setInterval(() => {
    DAC.writeVoltage(DAC.CHANNEL_1, voltage);
    console.log(`🔊 DAC Voltage: ${voltage}V`);
    
    voltage += 0.1;
    if (voltage > 2.5) voltage = 0.5;
}, 2000);

// بررسی وضعیت
setInterval(() => {
    let status = DAC.getStatus();
    console.log(`DAC Status - CH0: ${status.channel0}, CH1: ${status.channel1}`);
}, 3000);
```

---

## ۱۴. ⚡ **ماژول DMA**

### **توابع اصلی**
```javascript
// پیکربندی DMA برای ADC به DAC
DMA.startAdcToDac(0, 0, 1000, 512); // ADC0 به DAC0، نرخ 1kHz، بافر 512

// شروع انتقال
DMA.startTransfer();

// توقف انتقال
DMA.stopTransfer();

// تغییر نرخ نمونه‌برداری
DMA.setSampleRate(2000); // 2kHz

// خواندن آخرین نمونه
let sample = DMA.readSample();

// دریافت وضعیت
let status = DMA.getStatus();
```

### **مثال کاربردی**
```javascript
// پردازش سیگنال real-time
console.log("Initializing DMA for real-time processing...");

// پیکربندی DMA برای نمونه‌برداری از ADC و نوشتن روی DAC
DMA.startAdcToDac(0, 0, 1000, 1024); // 1kHz, بافر 1024 نمونه

// شروع انتقال real-time
DMA.startTransfer();

// مانیتورینگ وضعیت
setInterval(() => {
    let status = DMA.getStatus();
    console.log(`📊 DMA Status - Rate: ${status.sample_rate}Hz, Buffer: ${status.buffer_usage}%`);
    
    // خواندن آخرین نمونه
    let sample = DMA.readSample();
    if (sample !== -1) {
        console.log(`Latest sample: ${sample}`);
    }
}, 1000);

// تغییر نرخ نمونه‌برداری بعد از 10 ثانیه
setTimeout(() => {
    DMA.setSampleRate(2000); // افزایش به 2kHz
    console.log("Sample rate increased to 2kHz");
}, 10000);

// توقف بعد از 30 ثانیه
setTimeout(() => {
    DMA.stopTransfer();
    console.log("DMA transfer stopped");
}, 30000);
```

---

## ۱۵. 🌐 **ماژول Mongoose**

### **توابع اصلی**
```javascript
// ایجاد سرور HTTP
Net.httpListen("http://0.0.0.0:80");

// ایجاد HTTP کلاینت
Net.httpConnect("http://api.example.com");

// ارسال درخواست HTTP
Net.httpRequest("http://api.example.com/data", "GET", "");

// اتصال WebSocket
Net.wsConnect("ws://echo.websocket.org");

// ارسال داده WebSocket
Net.wsSend("Hello WebSocket!", Net.WS_OP_TEXT);

// مدیریت رویدادها
Net.poll(1000); // Poll every second
```

### **مثال کاربردی**
```javascript
// سرور REST API ساده
console.log("Starting HTTP server...");

// ایجاد سرور HTTP روی پورت 8080
if (Net.httpListen("http://0.0.0.0:8080")) {
    console.log("✅ HTTP server started on port 8080");
    
    // تعریف route ها
    Net.get("/", function(req, res) {
        return {
            status: 200,
            body: JSON.stringify({ 
                message: "Hello from ESP32!", 
                version: "1.0",
                free_heap: process.memoryUsage().free
            }),
            headers: { "Content-Type": "application/json" }
        };
    });
    
    Net.get("/api/status", function(req, res) {
        return {
            status: 200,
            body: JSON.stringify({
                device: "ESP32",
                uptime: process.uptime(),
                wifi: WiFi.status().sta
            }),
            headers: { "Content-Type": "application/json" }
        };
    });
    
    Net.post("/api/led", function(req, res) {
        let data = JSON.parse(req.body);
        if (data.state !== undefined) {
            gpio.write(2, data.state ? 1 : 0);
            return {
                status: 200,
                body: JSON.stringify({ success: true, led: data.state })
            };
        }
        return { status: 400, body: "Bad request" };
    });
    
    // Poll برای دریافت درخواست‌ها
    setInterval(() => {
        Net.poll(100);
    }, 100);
}

// کلاینت WebSocket
console.log("Connecting to WebSocket...");
if (Net.wsConnect("ws://echo.websocket.org")) {
    console.log("✅ WebSocket connected");
    
    // ارسال پیام هر 5 ثانیه
    setInterval(() => {
        let message = `Hello from ESP32 at ${Date.now()}`;
        Net.wsSend(message, Net.WS_OP_TEXT);
        console.log(`📤 Sent: ${message}`);
    }, 5000);
}
```

---

## ۱۶. 📨 **ماژول MQTT**

### **توابع اصلی**
```javascript
// شروع MQTT Broker
MQTT.brokerStart(1883, 10, false, "admin", "password");

// شروع MQTT Client
let clientSlot = MQTT.clientStart("mqtt://broker.local:1883", "esp32_client");

// انتشار پیام
MQTT.brokerPublish("evm/status", "Hello from Broker!");
MQTT.clientPublish(clientSlot, "sensors/temperature", "25.5");

// ثبت callback
MQTT.brokerOn("message", function(clientId, topic, message, qos) {
    console.log(`Broker received: ${topic} -> ${message}`);
});

MQTT.clientOn(clientSlot, "message", function(from, topic, message) {
    console.log(`Client received: ${topic} -> ${message}`);
});
```

### **مثال کاربردی**
```javascript
// سیستم کامل MQTT Broker + Client
console.log("🚀 Starting MQTT system...");

// شروع Broker
if (MQTT.brokerStart()) {
    console.log("✅ MQTT Broker started");
    
    // ثبت callback برای Broker
    MQTT.brokerOn("message", function(clientId, topic, message, qos) {
        console.log(`📨 Broker: [${topic}] ${message} from ${clientId} (QoS: ${qos})`);
        
        // پاسخ به پیام
        if (topic === "esp32/command") {
            if (message === "restart") {
                MQTT.brokerPublish("esp32/response", "Restarting...");
                setTimeout(() => {
                    process.exit(0);
                }, 1000);
            }
        }
    });
    
    MQTT.brokerOn("client", function(clientId, connected) {
        console.log(connected ? 
            `➕ Client connected: ${clientId}` : 
            `➖ Client disconnected: ${clientId}`);
    });
}

// شروع Client
let client = MQTT.clientStart("mqtt://127.0.0.1:1883", "esp32_main");
if (client >= 0) {
    console.log("✅ MQTT Client connected");
    
    // ثبت callback برای Client
    MQTT.clientOn(client, "connect", function(connected) {
        if (connected) {
            console.log("✅ Client connected to broker");
        }
    });
    
    MQTT.clientOn(client, "message", function(from, topic, message) {
        console.log(`📩 Client: [${topic}] ${message} from ${from}`);
    });
    
    // انتشار داده سنسور هر 10 ثانیه
    setInterval(() => {
        let temp = 20 + Math.random() * 10;
        let hum = 40 + Math.random() * 30;
        
        MQTT.clientPublish(client, "sensors/temperature", temp.toFixed(1));
        MQTT.clientPublish(client, "sensors/humidity", hum.toFixed(1));
        
        console.log(`📊 Published sensor data: ${temp.toFixed(1)}°C, ${hum.toFixed(1)}%`);
    }, 10000);
}

// انتشار وضعیت سیستم هر 30 ثانیه
setInterval(() => {
    let status = {
        uptime: process.uptime(),
        free_heap: process.memoryUsage().free,
        wifi: WiFi.status().sta,
        timestamp: Date.now()
    };
    
    MQTT.brokerPublish("evm/status", JSON.stringify(status));
}, 30000);
```

---

## ۱۷. 📂 **ماژول FTP**

### **توابع اصلی**
```javascript
// شروع FTP سرور
FTP.start(2121, "/sdcard", "admin", "password");

// بررسی وضعیت
let status = FTP.status();
console.log(`FTP running: ${status.running}, Port: ${status.port}`);

// توقف FTP
FTP.stop();

// تغییر تنظیمات
FTP.setPassword("newpassword");
FTP.setRootDir("/sdcard/files");

// اطلاعات اتصال
let info = FTP.getConnectionInfo();
```

### **مثال کاربردی**
```javascript
// راه‌اندازی FTP سرور برای انتقال فایل
console.log("Starting FTP server...");

// شروع FTP سرور
if (FTP.start(2121, "/sdcard", "esp32", "123456")) {
    console.log("✅ FTP server started");
    console.log("📁 Root directory: /sdcard");
    console.log("👤 Username: esp32");
    console.log("🔑 Password: 123456");
    
    let info = FTP.getConnectionInfo();
    console.log(`🌐 Connect via: ${info.connectionString}`);
    
    // مانیتورینگ وضعیت
    setInterval(() => {
        let status = FTP.status();
        if (status.running) {
            console.log(`🔄 FTP server active on port ${status.port}`);
        } else {
            console.log("❌ FTP server stopped");
        }
    }, 10000);
    
    // توقف خودکار بعد از 1 ساعت (برای امنیت)
    setTimeout(() => {
        FTP.stop();
        console.log("🛑 FTP server stopped automatically after 1 hour");
    }, 3600000);
} else {
    console.log("❌ Failed to start FTP server");
}

// استفاده از FTP Client (در دستگاه دیگر)
// ftp://esp32:123456@192.168.1.61:2121/
```

---

## ۱۸. 🎨 **ماژول LVGL**

### **توابع اصلی**
```javascript
// ایجاد آبجکت‌ها
let screen = lv.lv_scr_act();
let obj = lv.lv_obj_create(screen);

// مدیریت استایل
let style = lv.lv_style_create();
lv.lv_style_set_bg_color(style, lv.lv_color_hex(0xFF0000));
lv.lv_obj_add_style(obj, style, 0);

// ویجت‌ها
let label = lv.lv_label_create(screen);
let btn = lv.lv_btn_create(screen);
let slider = lv.lv_slider_create(screen);
```

### **مثال کاربردی**
```javascript
// ایجاد رابط کاربری ساده
console.log("Initializing LVGL UI...");

// صفحه اصلی
let screen = lv.lv_scr_act();

// استایل برای دکمه
let btnStyle = lv.lv_style_create();
lv.lv_style_set_bg_color(btnStyle, lv.lv_palette_main(lv.LV_PALETTE_BLUE));
lv.lv_style_set_radius(btnStyle, 10);

// دکمه اصلی
let button = lv.lv_btn_create(screen);
lv.lv_obj_set_size(button, 120, 50);
lv.lv_obj_set_pos(button, 60, 30);
lv.lv_obj_add_style(button, btnStyle, 0);

// متن دکمه
let btnLabel = lv.lv_label_create(button);
lv.lv_label_set_text(btnLabel, "Click Me!");
lv.lv_obj_center(btnLabel);

// لیبل وضعیت
let statusLabel = lv.lv_label_create(screen);
lv.lv_obj_set_pos(statusLabel, 20, 100);
lv.lv_label_set_text(statusLabel, "Status: Ready");

// اسلایدر
let slider = lv.lv_slider_create(screen);
lv.lv_obj_set_size(slider, 200, 20);
lv.lv_obj_set_pos(slider, 20, 150);
lv.lv_slider_set_range(slider, 0, 100);
lv.lv_slider_set_value(slider, 50, lv.LV_ANIM_OFF);

// ثبت event handlers
button.on('LV_EVENT_CLICKED', function() {
    lv.lv_label_set_text(statusLabel, "Status: Button Clicked!");
    lv.lv_style_set_bg_color(btnStyle, lv.lv_palette_main(lv.LV_PALETTE_GREEN));
    
    setTimeout(() => {
        lv.lv_label_set_text(statusLabel, "Status: Ready");
        lv.lv_style_set_bg_color(btnStyle, lv.lv_palette_main(lv.LV_PALETTE_BLUE));
    }, 2000);
});

slider.on('LV_EVENT_VALUE_CHANGED', function() {
    let value = lv.lv_slider_get_value(slider);
    lv.lv_label_set_text(statusLabel, `Slider: ${value}%`);
});

console.log("✅ LVGL UI initialized successfully");
```

---

## 🎯 **نکات مهم و بهترین روش‌ها**

### **مدیریت خطا**
```javascript
try {
    // کد پرخطا
    let data = fs.readFileSync("/nonexistent/file.txt");
} catch (error) {
    console.error(`❌ Error: ${error.message}`);
}
```

### **بهینه‌سازی عملکرد**
```javascript
// استفاده از setTimeout به جای setInterval برای عملیات سنگین
function processData() {
    // عملیات سنگین
    setTimeout(processData, 1000); // اجرای مجدد بعد از اتمام
}
processData();
```

### **مدیریت حافظه**
```javascript
// پاک‌سازی منابع
setInterval(() => {
    let heap = process.heapStats();
    if (heap.free < 10240) { // کمتر از 10KB
        console.warn("⚠️ Low memory! Freeing resources...");
        gc(); // فعال کردن garbage collector
    }
}, 30000);
```




    ✅ پین‌های ممنوعه: محافظت از پین‌های استفاده شده توسط لانچر
    ✅ خواندن/نوشتن GPIO: توابع اصلی برای کار با پین‌ها
    ✅ تنظیم جهت: INPUT/OUTPUT
    ✅ دکمه‌های لانچر: توابع مخصوص برای خواندن دکمه‌ها
    ✅ لیست پین‌های مجاز: برگرداندن پین‌های قابل استفاده
    ✅ توابع همزمان: برای کارهای ساده‌تر




ویژگی‌های ماژول Process:

    ✅ اطلاعات حافظه: process.memoryUsage()
    ✅ زمان فعالیت: process.uptime()
    ✅ استفاده CPU: process.cpuUsage()
    ✅ اطلاعات سیستم: process.arch, process.platform
    ✅ مدیریت پردازش: process.exit(), process.kill()
    ✅ آمار heap: process.heapStats()


ویژگی‌های ماژول Timer:

    ✅ تأخیر: Timer.delay(ms)
    ✅ تایمرهای یکباره: setTimeout(callback, ms)
    ✅ تایمرهای تکراری: setInterval(callback, ms)
    ✅ مدیریت تایمر: clearTimeout(id), clearInterval(id)
    ✅ زمان واقعی: setRealTime(h, m, s), getRealTime()
    ✅ زمان نسبی: setTime(h, m, s), getTimeString()
    ✅ مدیریت حافظه: پاک‌سازی خودکار منابع


 WiFi:

    ✅ مدیریت حالت‌ها: WiFi.mode("sta"), WiFi.mode("ap")
    ✅ اتصال STA: WiFi.sta("ssid", "password")
    ✅ ایجاد AP: WiFi.ap("ssid", "password", channel)
    ✅ اسکن شبکه‌ها: WiFi.scan()
    ✅ وضعیت: WiFi.status()
    ✅ آدرس IP: WiFi.staIP(), WiFi.apIP()
    ✅ اتصال خودکار: WiFi.autoConnect()
    ✅ مدیریت قدرت: WiFi.power(level)
    ✅ اطلاعات کامل: WiFi.info()


Mongoose:

    ✅ ساده‌تر برای استفاده
    ✅ HTTP/WebSocket آماده
    ✅ مستقل از libuv
    ✅ مناسب پروژه‌های کوچک

TCP/Libuv:

    ✅ کنترل کامل روی سوکت‌ها
    ✅ TLS/SSL پیشرفته
    ✅ سازگار با کدهای قدیمی EVM
    ✅ مناسب برنامه‌های شبکه پیچیده



🚀 ویژگی‌های ماژول MQTT:

    ✅ MQTT Broker کامل - می‌تونی سرور MQTT خودت رو راه‌اندازی کنی
    ✅ MQTT Client چندگانه - تا ۵ کلاینت همزمان
    ✅ Callbackهای Real-time - برای پیام‌ها، اتصال و قطع ارتباط
    ✅ QoS پشتیبانی - سطوح ۰، ۱ و ۲
    ✅ Retain Messages - پیام‌های ماندگار
    ✅ Authentication - احراز هویت اختیاری
    ✅ مدیریت وضعیت - مانیتورینگ کامل Broker و Clientها


✨   فایل سیستم مزایا:

    کنترل کامل کاربر روی استوریج
    پارامتر اختیاری استوریج (پیش‌فرض: AUTO)
    کپی بین استوریج‌ها
    لاگ‌گیری دقیق از محل عملیات
    بررسی سلامت استوریج قبل از عملیات




مزایای ساختار یکپارچه امبد ویرچال ماشین در این روش EVM:

    ✅ یکبار نوشتن، اجرا روی همه موتورها
    ✅ مدیریت آسان وابستگی‌ها
    ✅ قابلیت استفاده مجدد
    ✅ کامپوننت‌های تست شده

کدهایت رو بفرست:

    اول EVM های موجود (برای الگوبرداری)
    سپس ماژول‌های جدید
    فایل‌های .h مربوطه


    ✅ تبدیل کامل سینتکس MuJS به EVM
    ✅ حفظ تمام امکانات اصلی
    ✅ اضافه کردن مدیریت حافظه (evm_string_free)
    ✅ ترکیب با توابع EVM اصلی
    ✅ سازگاری با ساختار پروژه



QuickJS ✅

    از ES6+ کامل پشتیبانی میکنه
    let/const کاملاً ساپورت میشه
    توصیه: استفاده از let/const

MuJS ⚠️

    بیشتر ES5-oriented هست
    ممکنه با let مشکل داشته باشه
    توصیه: استفاده از var

EVM ✅

    از ES6 پشتیبانی میکنه
    let/const کار میکنه
    توصیه: استفاده از let/const

روال صحیح کار:

    ماژول‌های ESP32 موجود را بردارید
    تبدیل به EVM API کنید (به جای موتور-specific)
    در شاخه modules/esp/ قرار دهید
    اتوماتیک با تمام موتورها کار خواهد کرد

شما می‌خواهید ماژول‌های ESP32 را به روز کنید تا:
    ✅ با موتورهای مختلف کار کنند
    ✅ از EVM API استفاده کنند (نه binding مستقیم)
    ✅ مستقل از پلتفرم باشند




    ✅ مدیریت یکپارچه: همه peripheral ها با یک interface کار می‌کنن
    ✅ چندپلتفرمی: می‌تونی برای ESP32, Linux, Windows پیاده‌سازی کنی
    ✅ ناهمزمان: از libuv برای عملیات غیرمسدودکننده استفاده می‌کنه
    ✅ ماژولار: اضافه کردن peripheral جدید آسونه

ماژول‌های حیاتی که باید بسازی:
۱. GPIO (الویت اول)
c

typedef struct {
  evm_val_t jobject;
  iot_gpio_platform_data_t* platform_data;
  bool value;
  uint32_t pin;
  GpioDirection direction;  // INPUT/OUTPUT
  GpioMode mode;            // PULLUP/PULLDOWN/FLOAT
  GpioEdge edge;            // برای interrupt
} iot_gpio_t;

کاربرد در پروژه :

    کنترل LED ها، رله، سنسورها
    خواندن دکمه‌ها با حالت Pull-up
    interrupt برای events

۲. ADC (الویت بالا)

typedef struct {
  evm_val_t jobject;
  iot_adc_platform_data_t* platform_data;
  int32_t value;
} iot_adc_t;

کاربرد: خواندن سنسورهای آنالوگ (دما، رطوبت، نور، پتانسیومتر)
۳. PWM (الویت بالا)

typedef struct {
  evm_val_t jobject;
  iot_pwm_platform_data_t* platform_data;
  uint32_t pin;
  double duty_cycle;    // 0-100%
  double period;        // فرکانس
  bool enable;
} iot_pwm_t;

کاربرد:
    کنترل روشنایی LED
    کنترل سروو موتور
    تولید سیگنال‌های مختلف

۴. I2C (الویت متوسط)
typedef struct {
  evm_val_t jobject;
  iot_i2c_platform_data_t* platform_data;
  char* buf_data;
  uint8_t buf_len;
  uint8_t address;      // آدرس دستگاه
} iot_i2c_t;

کاربرد: ارتباط با سنسورهای I2C (مانند OLED, BME280, MPU6050)
۵. SPI (الویت متوسط)

typedef struct {
  evm_val_t jobject;
  iot_spi_platform_data_t* platform_data;
  SpiMode mode;
  uint32_t max_speed;
  char* tx_buf_data;
  char* rx_buf_data;
  uint8_t buf_len;
} iot_spi_t;

کاربرد: ارتباط با LCD, SD Card, سنسورهای SPI
۶. UART (الویت متوسط)

typedef struct {
  int device_fd;
  unsigned baud_rate;
  uint8_t data_bits;
  char *buf_data;
  unsigned buf_len;
} iot_uart_t;


📱 کاربر → 📁 spiffs/apps/ → 🎯 app_manager.c → 🔧 evm.c 
         → ⚙️ موتور JS (QuickJS/MuJS/JerryScript) → 🔌 ماژول‌ها 
         → 🖥️ LCD/سخت‌افزار
تست ساده از  اس  پیف 



📱 کاربر → 📁 sdcard/apps/ → 🎯 app_manager.c → 🔧 evm.c 
         → ⚙️ موتور JS (QuickJS/MuJS/JerryScript) → 🔌 ماژول‌ها 
         → 🖥️ LCD/سخت‌افزار

JavaScript API ← EVM Core ← Peripheral Common ← Platform Specific (ESP32/Linux/Windows)


### ویژگی‌های اصلی

- **ماشین مجازی JavaScript**: اجرای برنامه‌های JS با موتور 
- **مدیریت برنامه‌ها**: اسکن خودکار و مدیریت برنامه‌های نصب شده
- **رابط کاربری گرافیکی**: رابط کاربری زیبا با LVGL 8
- **پشتیبانی از سخت‌افزار**:
  - LCD نمایشگر 160x128
  - کارت حافظه SD
  - دکمه‌های فیزیکی (UP, DOWN, SELECT, BACK)
  - GPIO، تایمر، ADC، PWM
- **سیستم ماژولار**: ماژول‌های قابل گسترش برای قابلیت‌های مختلف
کاربرد: ارتباط سریال با GPS, GSM, Bluetooth modules
🚀 الویت‌بندی برای ساخت:
فاز ۱ (ضروری):

    GPIO - همین الان داری روش کار می‌کنی
    ADC - برای سنسورهای آنالوگ
    PWM - برای کنترل موتور و LED

فاز ۲ (مفید):
    I2C - برای سنسورهای پیشرفته
    UART - برای ارتباط سریال

فاز ۳ (تکمیلی):
    SPI - برای دستگاه‌های خاص
💡 ویژگی‌های مشترک همه ماژول‌ها:

// همه اینها رو دارن:
void iot_periph_call_async();  // عملیات ناهمزمان
IOT_DEFINE_PERIPH_CREATE_FUNCTION(); // ساخت خودکار



### معماری سیستم

- **هسته 0 (PRO CPU)**: لانچر اصلی و رابط کاربری
- **هسته 1 (APP CPU)**: اجرای برنامه‌های EVM
- **مدیریت منابع مشترک**: LCD، SD Card، دکمه‌ها

## 🏗️ معماری سیستم

🎯 درک معماری پیشنهادی

   یک لایه انتزاعی (EVM) ایجاد کنید که با موتورهای JS مختلف کار کند
    ماژول‌های مشترک بنویسید که روی تمام موتورها کار کنند
    مدیریت سخت‌افزار متمرکز داشته باشید
    از LVGL برای GUI استفاده کنید

🎯 معماری نهایی پیشنهادی
text

Core 0 (PRO_CPU)        Core 1 (APP_CPU)
     ↓                       ↓
[Launcher UI]          [EVM Engine]
     |                       |
[LVGL Tasks]          [JS Execution]
     |                       |
[Input Events]        [Hardware Modules]
     |                       |
[App Launcher] ←→ [Shared Resources]









---

curl -u esp32:123456 -T app/upload.js "ftp://192.168.1.61/apps/ud_test.js" --limit-rate 10k -v
curl -u esp32:123456 -v "ftp://192.168.1.61/shhab/Shahab Kamoei - Asir.mp3" -o komile.mp3 --limit-rate 1000k


lftp -u esp32,123456 ftp://192.168.1.61

2. اتصال با پورت مشخص:
bash

lftp -u esp32,123456 -p 21 ftp://192.168.1.61

🔄 دستورات داخل lftp:
Navigation:
lftp

pwd                         # نمایش مسیر جاری
ls                          # لیست فایل‌ها
ls -la                      # لیست با جزئیات
cd /                        # تغییر به روت

آپلود فایل:
lftp

put app/upload.js           # آپلود فایل
put app/upload.js -o new_name.js  # آپلود با نام جدید
mput *.js                   # آپلود چندین فایل

put spiffs/clok.js -o apps/main.js



دانلود فایل:
lftp

get ud_test.js              # دانلود فایل
get ud_test.js -o local.js  # دانلود با نام جدید
mget *.js                   # دانلود چندین فایل

مدیریت فایل:
lftp

rm ud_test.js               # حذف فایل
mkdir test_dir              # ساخت پوشه
rmdir test_dir              # حذف پوشه
rename old.js new.js        # تغییر نام



lftp -e "set net:limit-rate 100000; put -c spiffs/thermostat.js -o /apps/thermostat.js; quit" -u esp32,123456 192.168.1.61




تست ساده برای ای اس \ی 
``` C
#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include <inttypes.h>
#include "nvs_flash.h"
#include "esp_psram.h"

// استفاده از hardware_manager که قبلاً کار می‌کرد
#include "hardware_manager.h"
#include "evm.h"

static const char *TAG = "evm_main";

// تعاریف مدیریت حافظه برای EVM
#define zmalloc(size) heap_caps_malloc(size, MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT)
#define zfree(p) heap_caps_free(p)
#define zrealloc(p, size) heap_caps_realloc(p, size, MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT)

void *evm_malloc(size_t size) {
    void * m = zmalloc(size);
    if( m )
        memset(m, 0 ,size);
    return m;
}

void evm_free(void * p) {
    if(p)
        zfree(p);
}

void *evm_realloc(void * p, size_t size) {
    return zrealloc(p, size);
}

// تابع main EVM
void evm_main(char *filename) {
    ESP_LOGI(TAG, "🚀 Starting EVM on ESP32...");
    
    // بررسی وضعیت PSRAM
    if (esp_psram_is_initialized()) {
        size_t free_psram = heap_caps_get_free_size(MALLOC_CAP_SPIRAM);
        ESP_LOGI(TAG, "✅ PSRAM available: %d KB free", (int)free_psram/1024);
    }
    
    evm_t *e = evm_init();
    if (!e) {
        ESP_LOGE(TAG, "❌ Failed to initialize EVM");
        return;
    }
    
    ESP_LOGI(TAG, "📁 Running file: %s", filename);
    evm_run_file(e, EVM_UNDEFINED, filename);
    
    ESP_LOGI(TAG, "✅ EVM execution completed");
}

// ==================== تابع اصلی ====================

void app_main(void) {
    ESP_LOGI(TAG, "=================================");
    ESP_LOGI(TAG, "   EVM on ESP32 + Hardware Manager");
    ESP_LOGI(TAG, "=================================");
    
    // 1. Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        nvs_flash_init();
    }
    
    // 2. Initialize PSRAM
    esp_psram_init();
    
    // 3. راه‌اندازی تمام سخت‌افزارها با hardware_manager - این مهم است!
    ESP_LOGI(TAG, "🔧 Initializing all hardware with hardware_manager...");
    if (hardware_init_all() != ESP_OK) {
        ESP_LOGE(TAG, "❌ Hardware initialization failed!");
        return;
    }
    
    // 4. نمایش وضعیت سخت‌افزار
    ESP_LOGI(TAG, "📊 Hardware Status:");
    ESP_LOGI(TAG, "  LCD: ✅ Ready (via hardware_manager)");
    ESP_LOGI(TAG, "  SD Card: %s", hardware_is_sd_mounted() ? "✅ Mounted" : "❌ Failed");
    ESP_LOGI(TAG, "  WiFi: %s", hardware_is_wifi_ready() ? "✅ Started" : "❌ Failed");
    
    if (hardware_is_wifi_ready()) {
        ESP_LOGI(TAG, "  AP IP: %s", hardware_get_ap_ip());
        if (hardware_wifi_is_sta_connected()) {
            ESP_LOGI(TAG, "  STA IP: %s", hardware_get_sta_ip());
        }
    }
    
    // 5. اجرای اسکریپت اصلی
    char *main_script = "/spiffs/main.js";
    
    // بررسی وجود فایل
    FILE *f = fopen(main_script, "r");
    if (f) {
        fclose(f);
        ESP_LOGI(TAG, "Found main script: %s", main_script);
        evm_main(main_script);
    } else {
        ESP_LOGW(TAG, "Main script not found: %s", main_script);
        ESP_LOGI(TAG, "Creating example script...");
        
        // ایجاد یک اسکریپت مثال
        FILE *example = fopen("/spiffs/example.js", "w");
        if (example) {
            fprintf(example, "// EVM Example Script with Hardware Manager\n");
            fprintf(example, "print('Hello from ESP32!');\n");
            fprintf(example, "print('All hardware initialized via hardware_manager');\n");
            fprintf(example, "for(let i=0; i<3; i++) {\n");
            fprintf(example, "  print('Count:', i);\n");
            fprintf(example, "}\n");
            fclose(example);
            ESP_LOGI(TAG, "Example script created: /spiffs/example.js");
            
            // اجرای اسکریپت مثال
            evm_main("/spiffs/example.js");
        }
    }
    
    ESP_LOGI(TAG, "=================================");
    ESP_LOGI(TAG, "       System Ready!");
    ESP_LOGI(TAG, "=================================");
    
    // حلقه اصلی
    while(1) {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

```

**این راهنما بهت کمک می‌کنه:**
- ✅ سریع APIها رو پیدا کنی
- ✅ نمونه کدهای آماده داشته باشی  
- ✅ با لینوکس مقایسه کنی
- ✅ توسعه‌دهندگان جدید رو راهنمایی کنی


**کاملاً درسته! یک راهنمای کامل برای کلمات کلیدی JavaScript و APIهای ماژول‌ها می‌سازم:**

# 📚 **راهنمای کامل APIهای EVM برای ESP32**

## 🎯 **کلمات کلیدی JavaScript در پروژه**

### **۱. ماژول Console (کنترل خروجی)**
```javascript


🎯 مثال استفاده در جاوااسکریپت:
javascript

// فعال‌سازی DAC
DAC.enable(DAC.CHANNEL_0);

// تولید سیگنال سینوسی 1kHz به مدت 2 ثانیه
DAC.generateSine(DAC.CHANNEL_0, 1000, 2000);

// تنظیم ولتاژ خاص
DAC.writeVoltage(DAC.CHANNEL_0, 1.5); // 1.5 ولت

// تنظیم مقدار دیجیتال
DAC.write(DAC.CHANNEL_1, 128); // نیمه scale

// دریافت وضعیت
let status = DAC.getStatus();
console.log("Channel 0 enabled:", status.channel0);

⚡ مشخصات فنی DAC در ESP32:

    ۲ کانال مستقل
    کانال ۰: GPIO25
    کانال ۱: GPIO26

    رزولوشن: ۸ بیت (۲۵۶ سطح)
    محدوده ولتاژ: ۰ تا ۳.۳ ولت
    سرعت به روزرسانی: محدود توسط نرم‌افزار

این ماژول می‌تونه برای کاربردهای مختلفی مثل:
    تولید سیگنال‌های تست
    کنترل ولتاژ آنالوگ
    مدارهای صوتی ساده
    کنترل موتور/سروو

🎯 ویژگی‌های ماژول:

    ۱۰ پین تاچ پشتیبانی می‌کند
    خواندن مقادیر خام و فیلترشده
    تنظیم آستانه دلخواه
    تشخیص لمس خودکار
    کالیبراسیون هوشمند
    خواندن گروهی تمام پین‌ها

این ماژول برای ساخت رابط‌های لمسی، کلیدهای لمسی و تشخیص حضور مناسب است.

🎯 تغییرات مهم:

    touch_global_init(): فقط تنظیمات global بدون کانفیگ پین‌ها
    touch_configure_pin(): کانفیگ فقط پین خاص درخواستی
    touch_pin_configured[]: ردیابی پین‌های کانفیگ شده
    evm_touch_deinit(): آزادسازی پین وقتی دیگر نیاز نیست
    evm_touch_read_all(): فقط پین‌های کانفیگ شده را می‌خواند

📋 استفاده ایمن:
javascript

// فقط پین 0 را استفاده کن - پین‌های دیگر دست نخورده باقی می‌مانند
let value = Touch.read(Touch.PIN_0);
// پین 1 را برای کار دیگری استفاده کن
let value2 = Touch.read(Touch.PIN_1);
// وقتی کار پین تمام شد، آن را آزاد کن
Touch.deinit(Touch.PIN_0);
// فقط پین‌های کانفیگ شده را بخوان
let activePins = Touch.readAll();
// استفاده با نام GPIO
let touchValue = Touch.read(Touch.GPIO_4);  // معادل PIN_0
// ADC
let voltage = ADC.read(ADC.CHANNEL_0);
let raw = ADC.readRaw(ADC.CHANNEL_1);
// PWM
PWM.write(12, 1000, 50);  // پین 12، فرکانس 1kHz، duty cycle 50%
PWM.stop(12);

// I2C
I2C.begin(21, 22, 100000);  // SDA=21, SCL=22, فرکانس 100kHz
I2C.write(0x68, 0x6B, 0x00);  // نوشتن روی آدرس 0x68
let data = I2C.read(0x68, 0x3B);  // خواندن از آدرس 0x68

// SPI
SPI.begin(23, 19, 18, 1000000);  // MOSI=23, MISO=19, SCLK=18, فرکانس 1MHz
let received = SPI.transfer(0x55);  // ارسال و دریافت داده
SPI.write(0xAA);  // فقط ارسال داده

// UART
UART.begin(115200, 1, 3);  // Baud=115200, TX=1, RX=3
UART.write("Hello ESP32!");
if (UART.available() > 0) {
    let data = UART.read();
}


// چاپ اطلاعات
console.log("Hello World");
console.info("Information");
console.warn("Warning");
console.error("Error");

// دیباگ (فقط در حالت دیباگ)
console.debug("Debug message");

// مدیریت کنسول
console.clear();          // پاک کردن کنسول
console.trace();          // نمایش stack trace

// تایمر
console.time("label");    // شروع تایمر
console.timeEnd("label"); // پایان تایمر

// چاپ بدون خط جدید
console.write("text");
```

### **۲. ماژول FileSystem (مدیریت فایل)**
```javascript
// خواندن/نوشتن فایل
fs.readFileSync("/sdcard/file.txt");
fs.writeFileSync("/sdcard/file.txt", "content");

// بررسی وجود فایل
fs.existsSync("/sdcard/file.txt");

// مدیریت دایرکتوری
fs.readdirSync("/sdcard");
fs.mkdir("/sdcard/newfolder");
fs.rmdir("/sdcard/folder");

// اطلاعات فایل
fs.statSync("/sdcard/file.txt");

// حذف فایل
fs.unlink("/sdcard/file.txt");

// بررسی وضعیت
fs.getStatus();
```

### **۳. ماژول GPIO (کنترل سخت‌افزار)**
```javascript
// روش قدیم (ساده)
gpio.read(12);
gpio.write(12, 1);
gpio.setDirection(12, gpio.OUTPUT);

// خواندن دکمه‌ها
gpio.readButton(gpio.BUTTON_UP);
gpio.readButton(gpio.BUTTON_SELECT);

// پین‌های مجاز
gpio.getAvailablePins();

// ثابت‌ها
gpio.INPUT, gpio.OUTPUT
gpio.LOW, gpio.HIGH
gpio.BUTTON_UP, gpio.BUTTON_SELECT, gpio.BUTTON_DOWN, gpio.BUTTON_BACK
```

### **۴. ماژول Process (اطلاعات سیستم)**
```javascript
// حافظه
process.memoryUsage();

// زمان فعالیت
process.uptime();

// استفاده CPU
process.cpuUsage();

// اطلاعات سیستم
process.arch;        // "esp32"
process.platform;    // "esp32" 
process.pid;         // ID پردازش
process.versions;    // نسخه‌ها

// مدیریت پردازش
process.exit(0);
process.kill();

// دایرکتوری
process.cwd();
process.chdir("/new/path");

// آمار حافظه
process.heapStats();
```

### **۵. ماژول Timer (تایمر و زمان)**
```javascript
// تأخیر
Timer.delay(1000);   // 1 ثانیه

// زمان سیستم
Timer.getTime();     // میلی‌ثانیه

// تایمرهای JavaScript
let timeoutId = Timer.setTimeout(() => {
    console.log("Timeout!");
}, 1000);

let intervalId = Timer.setInterval(() => {
    console.log("Interval!");
}, 2000);

// توقف تایمر
Timer.clearTimeout(timeoutId);
Timer.clearInterval(intervalId);

// زمان واقعی
Timer.setTime(14, 30, 0);      // ساعت 14:30:00
Timer.setRealTime(10, 0, 0);   // ساعت واقعی 10:00:00

// خواندن زمان
let time = Timer.getRealTime();
console.log(time.hours, time.minutes, time.seconds);

Timer.getTimeString();  // "14:30:00"
```

### **۶. ماژول WiFi (شبکه)**
```javascript
// مقداردهی اولیه
WiFi.init();

// تنظیم حالت
WiFi.mode("sta");    // Station
WiFi.mode("ap");     // Access Point
WiFi.mode("both");   // هر دو

// اتصال به WiFi
WiFi.sta("SSID", "password");

// ایجاد نقطه دسترسی
WiFi.ap("AP_SSID", "password", 6);

// اسکن شبکه‌ها
let networks = WiFi.scan();

// وضعیت
let status = WiFi.status();
console.log(status.sta, status.ap, status.staIP, status.apIP);

// آدرس IP
WiFi.staIP();
WiFi.apIP();

// اطلاعات کامل
WiFi.info();

// مدیریت پیشرفته
WiFi.autoConnect();
WiFi.setAutoReconnect(true);
WiFi.maintain();
```

## 🔧 **ثابت‌های مهم**

### **GPIO:**
```javascript
// جهت
gpio.INPUT    = 0
gpio.OUTPUT   = 1

// سطح
gpio.LOW      = 0  
gpio.HIGH     = 1

// دکمه‌ها
gpio.BUTTON_UP      = 0
gpio.BUTTON_SELECT  = 1
gpio.BUTTON_DOWN    = 2
gpio.BUTTON_BACK    = 3
```

### **Process:**
```javascript
process.arch        // "esp32", "esp32s3", etc.
process.platform    // "esp32"
process.env         // "production"
```

## 🚀 **نمونه کدهای کاربردی**

### **کنترل LED:**
```javascript
// روشن کردن LED روی پین 12
gpio.setDirection(12, gpio.OUTPUT);
gpio.write(12, gpio.HIGH);

// چشمک زدن LED
Timer.setInterval(() => {
    let state = gpio.read(12);
    gpio.write(12, !state);
}, 500);



// استفاده از توابع استاتیک
GPIO.write(12, 1);  // روشن کردن پین 12
let value = GPIO.read(13);  // خواندن پین 13

// یا ایجاد instance
let led = GPIO.create(12, GPIO.Direction.OUT);
led.writeSync(1);

// استفاده از پین‌های از پیش تعریف شده
GPIO.write(GPIO.Pins.PIN_12, 1);
```

### **خواندن سنسور:**
```javascript
// خواندن دکمه UP
let buttonState = gpio.readButton(gpio.BUTTON_UP);
console.log("Button UP:", buttonState);
```

### **مدیریت فایل:**
```javascript
// ذخیره داده در فایل
let data = {temperature: 25, humidity: 60};
fs.writeFileSync("/sdcard/data.json", JSON.stringify(data));

// خواندن داده
let content = fs.readFileSync("/sdcard/data.json");
let savedData = JSON.parse(content);
```

### **مانیتورینگ سیستم:**
```javascript
// نمایش وضعیت سیستم هر 5 ثانیه
Timer.setInterval(() => {
    let mem = process.memoryUsage();
    let cpu = process.cpuUsage();
    
    console.log(`Memory: ${mem.usage.toFixed(1)}% | CPU: ${cpu.total.toFixed(1)}%`);
}, 5000);
```

### **اتصال WiFi:**
```javascript
// اتصال خودکار به WiFi
if (WiFi.init()) {
    WiFi.autoConnect();
    
    // بررسی وضعیت هر 10 ثانیه
    Timer.setInterval(() => {
        let status = WiFi.status();
        if (status.sta) {
            console.log("Connected! IP:", status.staIP);
        }
    }, 10000);
}
```




##  **🎯 ماژول‌های شبکه جدید:**

###   ماژول Mongoose (HTTP/WebSocket)


// ایجاد HTTP سرور
Net.httpListen("http://0.0.0.0:80");

// ایجاد HTTP کلاینت
Net.httpConnect("http://api.example.com");

// ارسال درخواست HTTP
Net.httpRequest("http://api.example.com/data", "GET", "");

// اتصال WebSocket
Net.wsConnect("ws://echo.websocket.org");

// ارسال داده WebSocket
Net.wsSend("Hello WebSocket!", Net.WS_OP_TEXT);

// مدیریت رویدادها
Net.poll(1000); // Poll every second

// ثابت‌های رویداد
Net.EV_ERROR       // خطا
Net.EV_HTTP_MSG    // پیام HTTP
Net.EV_WS_MSG      // پیام WebSocket
Net.EV_WS_OPEN     // باز شدن WebSocket
Net.EV_CLOSE       // بسته شدن اتصال

// انواع داده WebSocket
Net.WS_OP_TEXT     // داده متنی
Net.WS_OP_BINARY   // داده باینری

### ** ماژول HTTP Parser **
javascript

// ایجاد پارسر
let parser = http_parser.create(http_parser.REQUEST);

// پارس کردن داده
parser.execute(bufferData);

// رویدادهای پارسر
parser.onUrl = function(data, length) { };
parser.onStatus = function(statusCode, statusText) { };
parser.onHeaderField = function(field, length) { };
parser.onHeaderValue = function(value, length) { };
parser.onBody = function(body, length) { };
parser.onHeadersComplete = function() { };
parser.onMessageBegin = function() { };
parser.onMessageComplete = function(statusCode) { };

// انواع پارسر
http_parser.REQUEST   // پارسر درخواست
http_parser.RESPONSE  // پارسر پاسخ

### ۹. ماژول TCP
javascript

// ایجاد اتصال TCP
let tcp = tcp.create();

// اتصال به سرور
tcp.connect("192.168.1.100", 8080, function(status) {
    console.log("Connection status:", status);
});

// ایجاد سرور TCP
tcp.bind("0.0.0.0", 8080);
tcp.listen(10, function() {
    console.log("Server listening");
});

// ارسال داده
tcp.write(bufferData, function(status) {
    console.log("Write status:", status);
});

// خواندن داده
tcp.readStart();

// مدیریت رویدادها
tcp.onconnection = function(status, client) { };
tcp.onread = function(socket, nread, isEof, buffer) { };
tcp.onclose = function() { };

// تنظیمات پیشرفته
tcp.setKeepAlive(true, 60); // Keep-alive هر 60 ثانیه

### ۱۰. ماژول TLS (SSL)
javascript

// ایجاد context امن
let tlsContext = tls.TlsContext({
    cert: "-----BEGIN CERTIFICATE-----...",
    key: "-----BEGIN PRIVATE KEY-----...",
    ca: "-----BEGIN CERTIFICATE-----..."
});

// ایجاد اتصال TLS
let tlsSocket = tls.TlsInit(socket, {
    isServer: false,
    rejectUnauthorized: true
}, tlsContext);

// اتصال به سرور امن
tlsSocket.connect("secure.example.com");

// خواندن داده امن
tlsSocket.read(buffer);

// نوشتن داده امن
tlsSocket.write(buffer, true); // true برای بستن اتصال

// رویدادها
tlsSocket.onhandshakedone = function(error, authorized) { };
tlsSocket.onread = function(buffer) { };
tlsSocket.onwrite = function(buffer) { };

### 🚀 نمونه کدهای شبکه:
سرور HTTP ساده:
javascript

// ایجاد سرور HTTP
if (Net.httpListen("http://0.0.0.0:8080")) {
    console.log("HTTP server started on port 8080");
    
    // Poll برای دریافت درخواست‌ها
    Timer.setInterval(() => {
        Net.poll(100);
    }, 100);
}

کلاینت WebSocket:
javascript

// اتصال به WebSocket
if (Net.wsConnect("ws://echo.websocket.org")) {
    console.log("WebSocket connected");
    
    // ارسال پیام هر 5 ثانیه
    Timer.setInterval(() => {
        Net.wsSend("Hello from ESP32!", Net.WS_OP_TEXT);
    }, 5000);
}

### سرور TCP:
javascript

let server = tcp.create();
server.bind("0.0.0.0", 8080);
server.listen(5);

server.onconnection = function(status, client) {
    if (status === 0) {
        console.log("New client connected");
        client.readStart();
        
        client.onread = function(socket, nread, isEof, buffer) {
            if (nread > 0) {
                console.log("Received:", buffer.toString());
                client.write(buffer, function(status) {
                    console.log("Echo sent, status:", status);
                });
            }
        };
    }
};



## 📋 **فایل کمکی برای لینوکس**

این راهنما می‌تونه به این صورت توسعه داده بشه:

```
docs/
├── javascript_api.md          # این فایل
├── linux_implementation.md    # پیاده‌سازی لینوکس
├── examples/                  # نمونه کدها
│   ├── gpio_examples.js
│   ├── fs_examples.js
│   └── wifi_examples.js
└── api_reference/            # مرجع کامل API
    ├── console_api.md
    ├── fs_api.md
    └── ...
```


## 🎯 راهنمای استفاده در JavaScript:


### // شروع FTP سرور با تنظیمات پیش‌فرض
```javascript
FTP.start();

// شروع با تنظیمات سفارشی
FTP.start(2121, "/sdcard/downloads", "admin", "mypassword");

// بررسی وضعیت
let status = FTP.status();
console.log("FTP running:", status.running);
console.log("Port:", status.port);
console.log("IP:", status.localIP);

// دریافت اطلاعات اتصال
let info = FTP.getConnectionInfo();
console.log("Connect via:", info.connectionString);

// تغییر پسورد
FTP.setPassword("newsecurepassword");

// تغییر مسیر ریشه
FTP.setRootDir("/sdcard/files");

// توقف FTP سرور
FTP.stop();

// بررسی فعال بودن
if (FTP.isRunning()) {
    console.log("FTP server is active");
}

// استفاده از ثابت‌های پیش‌فرض
console.log("Default port:", FTP.DEFAULT_PORT);
console.log("Default user:", FTP.DEFAULT_USERNAME);

```


// ==================== MQTT BROKER ====================

## شروع MQTT Broker با تنظیمات پیش‌فرض
```javascript

MQTT.brokerStart();

// شروع با تنظیمات سفارشی
MQTT.brokerStart(1883, 10, false, "admin", "password");

// تنظیم callback برای پیام‌ها
MQTT.brokerOn("message", function(clientId, topic, message, qos) {
    console.log(`📨 Broker Message from ${clientId}: [${topic}] ${message} (QoS: ${qos})`);
});

// تنظیم callback برای اتصال/قطع کلاینت‌ها
MQTT.brokerOn("client", function(clientId, connected) {
    if (connected) {
        console.log(`🎉 Client connected: ${clientId}`);
    } else {
        console.log(`🔌 Client disconnected: ${clientId}`);
    }
});

// انتشار پیام از Broker
MQTT.brokerPublish("evm/status", "Hello from Broker!");
MQTT.brokerPublish("sensors/temperature", "25.5", MQTT.QOS_1, true);

// انتشار وضعیت سیستم
MQTT.brokerPublishStatus();

// دریافت وضعیت Broker
let brokerStatus = MQTT.brokerStatus();
console.log("Broker running:", brokerStatus.running);
console.log("Clients connected:", brokerStatus.clientCount);

// توقف Broker
MQTT.brokerStop();
```


## // ==================== MQTT CLIENT ====================
```javascript
// شروع MQTT Client
let clientSlot = MQTT.clientStart("mqtt://192.168.1.100:1883", "esp32_client");

// تنظیم callback برای کلاینت
MQTT.clientOn(clientSlot, "connect", function(connected) {
    if (connected) {
        console.log("✅ Client connected to broker");
    }
});

MQTT.clientOn(clientSlot, "message", function(clientId, topic, message) {
    console.log(`📨 Client Message: [${topic}] ${message} from ${clientId}`);
});

MQTT.clientOn(clientSlot, "disconnect", function(reason) {
    console.log("🔌 Client disconnected:", reason);
});

// انتشار پیام از کلاینت
MQTT.clientPublish(clientSlot, "test/topic", "Hello from ESP32!");
MQTT.clientPublish(clientSlot, "sensors/humidity", "60.5", MQTT.QOS_0, false);

// توقف کلاینت
MQTT.clientStop(clientSlot);

// ==================== تست کامل Broker + Client ====================

function startCompleteMQTTTest() {
    console.log("🚀 Starting Complete MQTT Test...");
    
    // 1. شروع Broker
    if (!MQTT.brokerStart()) {
        console.log("❌ Failed to start broker");
        return;
    }
    
    // 2. تنظیم callback Broker
    MQTT.brokerOn("message", function(clientId, topic, message, qos) {
        console.log(`📨 Broker received from ${clientId}: [${topic}] ${message}`);
    });
    
    MQTT.brokerOn("client", function(clientId, connected) {
        console.log(connected ? `➕ ${clientId} connected` : `➖ ${clientId} disconnected`);
    });
    
    // 3. شروع Client
    let client = MQTT.clientStart("mqtt://127.0.0.1:1883", "test_client");
    
    if (client < 0) {
        console.log("❌ Failed to start client");
        return;
    }
    
    // 4. تنظیم callback Client
    MQTT.clientOn(client, "connect", function(connected) {
        if (connected) {
            console.log("✅ Client connected successfully");
            
            // شروع انتشار پیام‌های تست
            startTestMessages(client);
        }
    });
    
    MQTT.clientOn(client, "message", function(from, topic, message) {
        console.log(`📩 Client received: [${topic}] ${message} from ${from}`);
    });
}

function startTestMessages(clientSlot) {
    let counter = 0;
    
    // انتشار پیام هر 5 ثانیه
    setInterval(() => {
        // از Client به Broker
        let clientMsg = `Hello from Client ${counter}`;
        MQTT.clientPublish(clientSlot, "test/client", clientMsg);
        
        // از Broker به همه
        let brokerMsg = `Hello from Broker ${counter}`;
        MQTT.brokerPublish("test/broker", brokerMsg);
        
        // وضعیت سیستم
        MQTT.brokerPublishStatus();
        
        counter++;
    }, 5000);
}

// ==================== استفاده پیشرفته ====================

// مدیریت چندین کلاینت
let clients = [];

function startMultipleClients() {
    for (let i = 0; i < 3; i++) {
        let clientId = `client_${i}`;
        let slot = MQTT.clientStart("mqtt://broker.local:1883", clientId);
        
        if (slot >= 0) {
            clients.push(slot);
            
            MQTT.clientOn(slot, "message", function(from, topic, message) {
                console.log(`[${clientId}] Received: ${topic} -> ${message}`);
            });
        }
    }
}

// سیستم publish/subscribe داینامیک
let subscriptions = {};

function subscribe(topic, callback) {
    subscriptions[topic] = callback;
}

function publish(topic, message) {
    // ارسال به همه کلاینت‌های فعال
    clients.forEach(slot => {
        MQTT.clientPublish(slot, topic, message);
    });
}

// مثال استفاده:
subscribe("sensors/#", function(clientId, topic, message) {
    console.log(`Sensor data: ${topic} = ${message}`);
});

subscribe("commands/restart", function(clientId, topic, message) {
    console.log("Restart command received!");
    // اجرای دستور ریستارت
});

```


### 
📊 نمونه خروجی لاگ:
text

📡 Initializing EVM MQTT Module
✅ MQTT module registered successfully with 5 client slots

🌐 Starting MQTT Broker simulation...
Port: 1883, Max Clients: 10
✅ MQTT Broker simulation started on port 1883

📡 Starting MQTT Client simulation...
Broker: mqtt://127.0.0.1:1883
Client ID: test_client
✅ MQTT Client test_client connected

📤 Broker Publishing: [evm/status] {"counter":0,"free_heap":123456,"clients":1,"timestamp":1640995200000}
📨 Broker Message from test_client: [test/topic] Hello from ESP32!


// نوشتن با استوریج مشخص
fs.writeFile("/config.json", '{"name": "test"}', fs.SPIFFS);
fs.writeFile("/data.log", "log data", fs.SDCARD);

// خواندن با استوریج مشخص
let config = fs.readFile("/config.json", fs.SPIFFS);
let data = fs.readFile("/data.log", fs.SDCARD);

// خواندن با جستجوی خودکار
let file = fs.readFile("/somefile.txt"); // اول SPIFFS، سپس SD

// بررسی وجود در استوریج خاص
if (fs.exists("/config.json", fs.SPIFFS)) {
    console.log("Config exists in SPIFFS");
}

// حذف از استوریج خاص
fs.unlink("/oldfile.txt", fs.SDCARD);

// کپی بین استوریج‌ها
fs.copyFile("/spiffs/config.json", "/sdcard/backup.json", fs.SPIFFS, fs.SDCARD);

// وضعیت استوریج‌ها
let info = fs.getStorageInfo();
console.log("SPIFFS mounted:", info.spiffs.mounted);
console.log("SD Card mounted:", info.sdcard.mounted);

رزایا:

    کنترل کامل کاربر روی استوریج
    پارامتر اختیاری استوریج (پیش‌فرض: AUTO)
    کپی بین استوریج‌ها
    لاگ‌گیری دقیق از محل عملیات
   بررسی سلامت استوریج قبل از عملیات

حالا کاربر می‌تونه دقیقاً مشخص کنه از کدوم استوریج استفاده کنه! 🎯



📝 مثال استفاده در JavaScript:

```javascript

// ایجاد سرور REST API
Net.httpListen("http://0.0.0.0:8000");

// تعریف route های مختلف
Net.get("/", function(req, res) {
    console.log("GET / called");
    return {
        status: 200,
        body: JSON.stringify({ message: "Hello World!", version: "1.0" }),
        headers: { "Content-Type": "application/json" }
    };
});

Net.get("/api/info", function(req, res) {
    return {
        status: 200,
        body: JSON.stringify({ 
            device: "ESP32", 
            free_heap: ESP32.getFreeHeap(),
            sdk_version: ESP32.getSdkVersion()
        }),
        headers: { "Content-Type": "application/json" }
    };
});

Net.post("/api/echo", function(req, res) {
    const data = JSON.parse(req.body);
    return {
        status: 200,
        body: JSON.stringify({ echoed: data }),
        headers: { "Content-Type": "application/json" }
    };
});

// اجرای event loop
setInterval(function() {
    Net.poll(100);
}, 100);


```


🚀 ویژگی‌های این پیاده‌سازی:

    ✅ پشتیبانی از تمام متدهای HTTP: GET, POST, PUT, DELETE
    ✅ Route Registration: ثبت مسیرهای دلخواه
    ✅ JSON Support: پشتیبانی از JSON request/response
    ✅ CORS Support: پشتیبانی از CORS headers
    ✅ Event-Driven: معماری event-driven
    ✅ JavaScript Integration: اجرای handler ها در JavaScript

🎯 نمونه REST API کامل:


```javascript
// یک REST API کامل برای مدیریت TODOها
let todos = [];
let nextId = 1;

Net.get("/api/todos", (req, res) => ({
    status: 200,
    body: JSON.stringify(todos),
    headers: { "Content-Type": "application/json" }
}));

Net.post("/api/todos", (req, res) => {
    const todo = JSON.parse(req.body);
    todo.id = nextId++;
    todos.push(todo);
    return {
        status: 201,
        body: JSON.stringify(todo),
        headers: { "Content-Type": "application/json" }
    };
});

Net.delete("/api/todos/:id", (req, res) => {
    const id = parseInt(req.params.id);
    todos = todos.filter(t => t.id !== id);
    return {
        status: 200,
        body: JSON.stringify({ message: "Deleted" }),
        headers: { "Content-Type": "application/json" }
    };
});

```


## ⚡ مشخصات فنی:

    نرخ نمونه‌برداری: ۱۰۰Hz تا ۲۰kHz
    اندازه بافر: ۱۰ تا ۴۰۹۶ نمونه
    تبدیل داده: ۱۲-bit ADC → ۸-bit DAC
    کنترل دقیق زمان: با vTaskDelayUntil
    اولویت بالا: برای minimum jitter

این ماژول می‌تونه برای کاربردهای زیر استفاده بشه:
    🔊 پردازش صوت real-time
    📊 مانیتورینگ سیگنال‌های آنالوگ
    🎛️ کنترل حلقه فیدبک
    🔄 تبدیل داده‌های سنسور


```javascript
// پیکربندی DMA برای ADC0 به DAC0 با نرخ 1kHz
DMA.startAdcToDac(0, 0, 1000, 512);

// شروع انتقال real-time
DMA.startTransfer();

// تغییر نرخ نمونه‌برداری به 2kHz
DMA.setSampleRate(2000);

// مانیتورینگ وضعیت
setInterval(() => {
    let status = DMA.getStatus();
    console.log(`Rate: ${status.sample_rate}Hz, Buffer: ${status.buffer_usage}%`);
    
    // خواندن آخرین نمونه
    let sample = DMA.readSample();
    if (sample !== -1) {
        console.log("Latest sample:", sample);
    }
}, 1000);

// توقف بعد از 10 ثانیه
setTimeout(() => {
    DMA.stopTransfer();
}, 10000);

```


# evm-esp32

LCD:      13, 14, 15
SD Card:  18, 19, 23, 5
Buttons:  2, 4, 34, 35
Relay:    32
Speaker:  33
DAC:      25, 26
I2C:      21, 22


TOUCH_PAD_NUM0: GPIO4   ✅ **آزاد است!**
TOUCH_PAD_NUM1: GPIO0   ⚠️ **پین boot** (اما استفاده نمی‌شه)
TOUCH_PAD_NUM2: GPIO2   ❌ **دکمه PLAY** (اشغال)
TOUCH_PAD_NUM3: GPIO15  ❌ **LCD CS** (اشغال)
TOUCH_PAD_NUM4: GPIO13  ❌ **LCD MOSI** (اشغال)
TOUCH_PAD_NUM5: GPIO12  ✅ **آزاد است!** (بهترین گزینه)
TOUCH_PAD_NUM6: GPIO14  ❌ **LCD CLK** (اشغال)
TOUCH_PAD_NUM7: GPIO27  ✅ **آزاد است!**
TOUCH_PAD_NUM8: GPIO33  ❌ **SPK_MODE** (اشغال)
TOUCH_PAD_NUM9: GPIO32  ❌ **RELAY** (اشغال)


پین‌های تاچ آزاد شما:

    GPIO12 = TOUCH_PAD_NUM5 = Touch.PIN_5
    GPIO27 = TOUCH_PAD_NUM7 = Touch.PIN_7



    ### راهنمای کامل ماژول `list` در EVM-ESP32 (برای جاوااسکریپت)

ماژول `list` یک لیست پیوندی پویا و سبک است که بهت اجازه می‌ده داده‌ها رو بدون محدودیت اندازه آرایه مدیریت کنی — عالی برای صف پیام‌ها، تاریخچه، لیست فایل‌ها یا هر داده پویا.

#### نحوه استفاده (بدون `require` — عمومی است!)

چون ماژول عمومی ثبت شده، مستقیم در دسترسه:

```javascript
// هیچ require لازم نیست!
var myList = list.create();  // لیست جدید بساز
```

#### توابع موجود

| تابع | توضیح | مثال |
|------|-------|------|
| `list.create()` | لیست جدید می‌سازه و برمی‌گردونه | `var myList = list.create();` |
| `list.append(list, data)` | داده رو به آخر لیست اضافه می‌کنه | `list.append(myList, "سلام");` |
| `list.len(list)` | تعداد آیتم‌ها رو برمی‌گردونه | `print(list.len(myList)); // 1` |
| `list.get(list, index)` | آیتم در اندیس مشخص رو برمی‌گردونه | `print(list.get(myList, 0)); // سلام` |
| `list.pop(list)` | آخرین آیتم رو حذف می‌کنه | `list.pop(myList);` |
| `list.clear(list)` | تمام لیست رو پاک می‌کنه | `list.clear(myList);` |

#### مثال کامل و کاربردی

```javascript
print("=== تست کامل ماژول list ===");

var myList = list.create();

// اضافه کردن آیتم‌ها
list.append(myList, "آیتم اول");
list.append(myList, "آیتم دوم");
list.append(myList, "آیتم سوم");

print("تعداد آیتم‌ها:", list.len(myList));  // 3

print("آیتم اول:", list.get(myList, 0));  // آیتم اول
print("آیتم آخر:", list.get(myList, list.len(myList)-1));  // آیتم سوم

// حذف آخرین آیتم
list.pop(myList);
print("پس از pop، تعداد:", list.len(myList));  // 2

// پاک کردن کامل
list.clear(myList);
print("پس از clear، تعداد:", list.len(myList));  // 0

print("تست با موفقیت به پایان رسید!");
```

#### کاربردهای واقعی

- **صف پیام‌ها** (نوتیفیکیشن)
- **تاریخچه دما** یا سنسورها
- **لیست فایل‌های یک پوشه** (با ترکیب `fs.readdir`)
- **صف کارهای پس‌زمینه**
- **مدیریت تنظیمات پویا**

#### نکته مهم

- داده‌ها به صورت **string** ذخیره می‌شن (چون `evm_mk_string` استفاده شده)
- اگر می‌خوای عدد یا آبجکت ذخیره کنی، اول به string تبدیل کن (مثل `String(123)`)

### خلاصه

```js
var list = list.create();  // ساخت
list.append(list, "داده"); // اضافه
list.len(list);            // تعداد
list.get(list, 0);         // خواندن
list.pop(list);            // حذف آخر
list.clear(list);          // پاک کردن
```

**ماژول `list` آماده استفاده است — ساده، سریع و بدون نیاز به require!**

اگر خواستی نسخه پیشرفته‌تر با `insert`, `remove`, `find`, `sort` یا ذخیره در فایل اضافه کنم، فقط بگو!


# راهنمای ساده کار با ماژول onewire

## 📌 مقدمه
ماژول `onewire` برای کار با سنسورهای دما و رطوبت استفاده می‌شود.

## 🔧 توابع موجود در ماژول onewire

### 1. جستجوی سنسورها
```javascript
var devices = onewire.search(پین);
```
**مثال:**
```javascript
// جستجو روی پین 21
var devices = onewire.search(21);
print("تعداد سنسور: " + devices.length);
```

### 2. خواندن دما از DS18B20
```javascript
var temp = onewire.readTemp(پین, آدرس);
```
**مثال:**
```javascript
// خواندن دما
var temp = onewire.readTemp(21, "28FF641A8B1603A4");
print("دما: " + temp + " درجه");
```

### 3. خواندن رطوبت از DHT
```javascript
var data = onewire.readDHT(پین, نوع);
```
**مثال:**
```javascript
// خواندن از DHT22 روی پین 22
var data = onewire.readDHT(22, 22);
if (data) {
    print("دما: " + data.temperature);
    print("رطوبت: " + data.humidity);
}
```

## 📝 مثال‌های ساده

### مثال ۱: پیدا کردن سنسورها
```javascript
print("=== جستجوی سنسور ===");
var pin = 21;
var devices = onewire.search(pin);

if (devices.length > 0) {
    print("✅ " + devices.length + " سنسور پیدا شد");
    for (var i = 0; i < devices.length; i++) {
        print("سنسور " + (i+1) + ":");
        print("  آدرس: " + devices[i].address);
        print("  خانواده: " + devices[i].familyCode);
    }
} else {
    print("❌ سنسوری پیدا نشد");
}
```

### مثال ۲: خواندن دما
```javascript
print("=== خواندن دما ===");
var pin = 21;

// اول جستجو کن
var devices = onewire.search(pin);
if (devices.length > 0) {
    // از اولین سنسور بخوان
    var temp = onewire.readTemp(pin, devices[0].address);
    print("🌡️ دما: " + temp + " درجه سانتی‌گراد");
} else {
    print("سنسور پیدا نشد!");
}
```

### مثال ۳: خواندن رطوبت
```javascript
print("=== خواندن رطوبت ===");
var pin = 22;
var type = 22; // DHT22

var data = onewire.readDHT(pin, type);
if (data) {
    print("💧 رطوبت: " + data.humidity + "%");
    print("🌡️ دما: " + data.temperature + "°C");
} else {
    print("خطا در خواندن DHT");
}
```

### مثال ۴: خواندن همزمان
```javascript
print("=== سیستم کامل ===");

var tempPin = 21;
var humPin = 22;

// خواندن دما
var devices = onewire.search(tempPin);
if (devices.length > 0) {
    var temp = onewire.readTemp(tempPin, devices[0].address);
    print("🔥 دما: " + temp.toFixed(1) + "°C");
}

// خواندن رطوبت
var dhtData = onewire.readDHT(humPin, 22);
if (dhtData) {
    print("💦 رطوبت: " + dhtData.humidity.toFixed(1) + "%");
}
```

### مثال ۵: حلقه خواندن پیوسته
```javascript
print("=== سیستم مانیتورینگ دما OneWire ===");
print("📌 پین: GPIO21 | 🔄 فرکانس: 1Hz | 🔢 تعداد خواندن: 5");

var ONEWIRE_PIN = 21;

// جستجوی دستگاه‌ها
var devices = onewire.search(ONEWIRE_PIN);

if (devices.length === 0) {
    print("🚫 دستگاه‌ای یافت نشد!");
    print("🔧 راهنمای عیب‌یابی:");
    print("   1. سیم‌کشی را بررسی کنید");
    print("   2. مقاومت pull-up 4.7kΩ را اضافه کنید");
    print("   3. اتصال VCC (3.3V) و GND را بررسی کنید");
} else {
    print("🎯 تعداد دستگاه‌های شناسایی شده:", devices.length);
    
    for (var i = 0; i < devices.length; i++) {
        var dev = devices[i];
        print("\n" + "═".repeat(40));
        print("🔍 دستگاه #" + (i+1));
        print("📋 آدرس:", dev.address.substring(0, 8) + "..." + dev.address.substring(24));
        print("🏭 خانواده:", dev.familyCode ? "DS18B20 (0x28)" : "نامشخص");
        
        // آرایه برای ذخیره مقادیر
        var readings = [];
        
        // خواندن ۵ باره با Timer.delay
        for (var reading = 1; reading <= 5; reading++) {
            var temp = onewire.readTemp(ONEWIRE_PIN, dev.address);
            
            if (temp > -900) {
                readings.push(temp);
                var tempF = (temp * 9/5) + 32;
                
                // نمایش پیشرفت
                var progress = "[" + "■".repeat(reading) + "□".repeat(5-reading) + "]";
                print("   " + progress + " خواندن " + reading + ": " + 
                      temp.toFixed(2) + "°C | " + tempF.toFixed(2) + "°F");
                
                // نمایش گرافیکی ساده
                var bars = Math.round((temp + 10) / 2); // مقیاس -10 تا 50 درجه
                bars = Math.max(0, Math.min(20, bars));
                var graph = "|" + "█".repeat(bars) + " ".repeat(20-bars) + "|";
                print("   " + graph + " ~" + temp.toFixed(1) + "°C");
                
            } else {
                print("   ❌ خطا در خواندن #" + reading);
            }
            
            // تاخیر 1 ثانیه با Timer.delay (1000 میلی‌ثانیه)
            if (reading < 5) {
                if (typeof Timer !== 'undefined') {
                    Timer.delay(1000);
                } else {
                    // اگر Timer وجود ندارد، busy wait
                    var start = get_time();
                    while (get_time() - start < 1000) {
                        // منتظر بمان
                    }
                }
            }
        }
        
        // محاسبات آماری
        if (readings.length > 0) {
            var sum = 0;
            var min = readings[0];
            var max = readings[0];
            
            for (var j = 0; j < readings.length; j++) {
                sum += readings[j];
                if (readings[j] < min) min = readings[j];
                if (readings[j] > max) max = readings[j];
            }
            
            var avg = sum / readings.length;
            
            print("\n📊 آمار دما:");
            print("   📈 متوسط: " + avg.toFixed(2) + "°C");
            print("   🔽 حداقل: " + min.toFixed(2) + "°C");
            print("   🔼 حداکثر: " + max.toFixed(2) + "°C");
            print("   📐 دامنه: " + (max - min).toFixed(2) + "°C");
            
            // تحلیل دمایی
            print("\n💡 تحلیل دمایی:");
            if (avg < 10) {
                print("   ❄️  دمای سرد");
            } else if (avg < 25) {
                print("   😊 دمای مطلوب");
            } else if (avg < 35) {
                print("   🔥 دمای گرم");
            } else {
                print("   ⚠️  دمای بسیار گرم");
            }
        }
    }
    
    print("\n" + "═".repeat(40));
    print("✅ مانیتورینگ کامل شد!");
    print("⏱️  زمان کل: ~5 ثانیه");
    print("📡 دستگاه‌های فعال: " + devices.length);
}
```

## ⚠️ نکات مهم

### ۱. کد خطا
اگر `readTemp` خطا بدهد، عدد **-999** برمی‌گرداند.

### ۲. بررسی وجود سنسور
همیشه اول `search` کنید، بعد `readTemp`:
```javascript
// ❌ غلط
var temp = onewire.readTemp(21, "آدرس"); // ممکن است خطا بدهد

// ✅ درست
var devices = onewire.search(21);
if (devices.length > 0) {
    var temp = onewire.readTemp(21, devices[0].address);
}
```

### ۳. DHT ممکن است null برگرداند
```javascript
var data = onewire.readDHT(22, 22);
if (data) {
    // موفق
} else {
    // خطا
}
```

## 🔌 سیم‌کشی

### برای DS18B20:
```
VCC  → 3.3V
DATA → GPIO (با مقاومت 4.7kΩ به VCC)
GND  → GND
```

### برای DHT:
```
VCC  → 3.3V
DATA → GPIO (با مقاومت 10kΩ به VCC)
GND  → GND
```

## 💡 مثال کاربردی نهایی
```javascript
print("=== برنامه عملی ===");

function readSensors() {
    // پین‌ها
    var tempPin = 21;
    var humPin = 22;
    
    // خواندن دما
    var devices = onewire.search(tempPin);
    if (devices.length === 0) {
        print("⚠️ سنسور دما پیدا نشد");
        return;
    }
    
    var temp = onewire.readTemp(tempPin, devices[0].address);
    if (temp < -900) {
        print("❌ خطا در خواندن دما");
    } else {
        print("🌡️ دمای اتاق: " + temp.toFixed(1) + "°C");
    }
    
    // خواندن رطوبت
    var dhtData = onewire.readDHT(humPin, 22);
    if (dhtData) {
        print("💧 رطوبت اتاق: " + dhtData.humidity.toFixed(1) + "%");
    } else {
        print("❌ خطا در خواندن رطوبت");
    }
}

// اجرای تابع
readSensors();
print("✅ برنامه پایان یافت");
```


# 📘 راهنمای کامل کد ماژول IR (مادون قرمز)

## 🎯 **هدف ماژول**
این ماژول برای **دریافت و ارسال سیگنال‌های مادون قرمز** در پلتفرم EVM طراحی شده است. از پروتکل‌های مختلف IR پشتیبانی می‌کند و امکان **ضبط و پخش مجدد** سیگنال‌ها را فراهم می‌سازد.

## 📋 **پروتکل‌های پشتیبانی شده**

| پروتکل | شناسه | توضیحات |
|--------|-------|---------|
| `NEC` | 1 | استاندارد رایج (LG، Panasonic) |
| `SONY` | 2 | پروتکل SIRC (12/15/20 بیتی) |
| `SAMSUNG` | 3 | پروتکل Samsung با آدرس 0xE0 |
| `LG` | 4 | مشابه NEC با آدرس 16 بیتی |
| `RC5` | 6 | پروتکل Philips RC5 |
| `RC6` | 7 | پروتکل Philips RC6 |
| `UNKNOWN` | 0 | پروتکل‌های ناشناخته |

## 🏗️ **ساختار داده‌ها**

### **1. ساختار `ir_decoded_data_t`**
```c
typedef struct {
    ir_protocol_t protocol;  // نوع پروتکل
    uint32_t address;        // آدرس دستگاه (0-255)
    uint32_t command;        // دستور (0-255)
    uint8_t bits;            // تعداد بیت‌های دریافتی
    bool repeat;             // آیا تکرار است؟
    bool valid;              // آیا دیکود موفق بود؟
    uint32_t raw_data;       // داده خام 32 بیتی
} ir_decoded_data_t;
```

### **2. متغیرهای گلوبال**
| متغیر | نوع | توضیحات |
|-------|------|---------|
| `pulses[]` | `uint32_t[MAX_PULSES]` | ذخیره پالس‌های دریافتی |
| `pulse_count` | `uint32_t` | تعداد پالس‌های ذخیره شده |
| `ir_result_queue` | `QueueHandle_t` | صف برای انتقال نتایج |
| `ir_task_handle` | `TaskHandle_t` | هندل تسک خواندن |
| `ir_task_running` | `bool` | وضعیت اجرای تسک |
| `current_ir_pin` | `int` | پین فعلی تنظیم شده |

## 🔧 **توابع اصلی ماژول**

### **1. `ir.start(pin)`**
```javascript
// مثال:
ir.start(21);  // شروع خواندن مداوم از پین 21
```
**وظیفه**: شروع خواندن مداوم IR  
**پارامترها**: `pin` (شماره پین GPIO)  
**خروجی**: `true` در صورت موفقیت

### **2. `ir.stop()`**
```javascript
// مثال:
ir.stop();  // توقف خواندن مداوم
```
**وظیفه**: توقف تسک خواندن مداوم  
**خروجی**: `true` در صورت موفقیت

### **3. `ir.get()`**
```javascript
// مثال:
var code = ir.get();
if (code) {
    print("Protocol: " + code.protocol);
    print("Command: " + code.command);
}
```
**وظیفه**: دریافت آخرین کد IR از صف  
**خروجی**: آبجکت IR یا `undefined` اگر کدی نباشد

### **4. `ir.read(pin, timeout)`**
```javascript
// مثال:
var code = ir.read(21, 500);  // خواندن تک‌باره با timeout 500ms
```
**وظیفه**: خواندن تک‌باره IR  
**پارامترها**: 
- `pin` (شماره پین)
- `timeout` (زمان انتظار به میلی‌ثانیه - اختیاری، پیش‌فرض 500)

### **5. `ir.raw()`**
```javascript
// مثال:
var csv = ir.raw();  // "4500,4500,560,1690,560,560,..."
print("Raw pulses: " + csv);
```
**وظیفه**: دریافت پالس‌های آخرین سیگنال به فرمت CSV  
**خروجی**: رشته CSV یا `undefined`

### **6. `ir.send(pin, data, frequency)`**
```javascript
// مثال 1: ارسال پالس‌های ذخیره شده
ir.send(21, 0, 38);  // ارسال آخرین پالس‌ها با فرکانس 38kHz

// مثال 2: ارسال پالس‌های دلخواه
ir.send(21, "9000,4500,560,560,560,1690,...", 38);
```
**وظیفه**: ارسال سیگنال IR  
**پارامترها**:
- `pin` (پین خروجی)
- `data` (رشته CSV یا 0 برای استفاده از آخرین پالس‌ها)
- `frequency` (فرکانس کیلوهرتز - اختیاری، پیش‌فرض 38)

### **7. `ir.status()`**
```javascript
// مثال:
var status = ir.status();
print("Running: " + status.running);
print("Queue: " + status.queue);
```
**وظیفه**: دریافت وضعیت ماژول  
**خروجی**: آبجکت شامل `running` و `queue`

## 📊 **خروجی آبجکت IR**

هنگام دریافت یک کد، آبجکت زیر برگردانده می‌شود:

```javascript
{
    protocol: "NEC",        // نام پروتکل (رشته)
    address: 0,             // آدرس (عدد)
    command: 69,            // دستور (عدد)
    bits: 32,               // تعداد بیت‌ها
    repeat: false,          // آیا تکرار است؟
    valid: true,            // آیا معتبر است؟
    raw: 0xFF00FF00,        // داده خام 32 بیتی
    hex: "0x0045",          // آدرس+دستور هگزادسیمال
    hex_full: "0xFF00FF00", // داده کامل هگزادسیمال
    decimal: "69"           // دستور دسیمال (رشته)
}
```

## ⚙️ **الگوریتم تشخیص پروتکل**

### **مراحل تشخیص:**
1. **آنالیز Leader** (اولین پالس و فضای اول)
2. **مقایسه با timing استاندارد**:
   ```
   NEC:      9000µs / 4500µs
   SAMSUNG:  4500µs / 4500µs  
   SONY:     2400µs / 600µs
   RC5:      900µs  / 900µs
   ```
3. **سقوط به NEC** در صورت عدم تشخیص

### **فرآیند دیکود NEC:**
```c
// 1. چک تکرار
if (pulse1≈9000µs && space1≈4500µs && pulse2≈560µs && space2≈2250µs)
    → کد تکرار

// 2. خواندن بیت‌ها (MSB-first)
if (space ≈ 1680µs) → بیت 1
if (space ≈ 560µs)  → بیت 0

// 3. استخراج 4 بایت:
// Byte1: آدرس
// Byte2: آدرس معکوس (برای صحت‌سنجی)
// Byte3: دستور  
// Byte4: دستور معکوس
```

### **فرآیند دیکود SONY:**
```c
// 1. چک Leader: 2400µs / 600µs
// 2. خواندن بیت‌ها (LSB-first)
if (space ≈ 1200µs) → بیت 1
if (space ≈ 600µs)  → بیت 0

// 3. بسته به تعداد بیت‌ها:
// 12-bit: 7-bit command + 5-bit address
// 15-bit: 7-bit command + 8-bit address  
// 20-bit: 7-bit command + 5-bit address + 8-bit extended
```

## 🔍 **توابع کمکی داخلی**

### **1. `in_range(value, min, max)`**
```c
// مثال:
if (in_range(pulse, 8500, 9500)) {
    // پالس در رنج NEC است
}
```
**وظیفه**: بررسی محدوده عددی

### **2. `is_logical_pulse(pulse)`**
```c
// منطق: 400-700 میکروثانیه
return (pulse >= 400 && pulse <= 700);
```

### **3. `is_logical_space(space)`**
```c
// منطق: 300-2000 میکروثانیه  
return (space >= 300 && space <= 2000);
```

### **4. `setup_ir_gpio(pin)`**
```c
// پیکربندی GPIO:
gpio_reset_pin(pin);
gpio_set_direction(pin, GPIO_MODE_INPUT);
gpio_set_pull_mode(pin, GPIO_PULLUP_ONLY);
```

## 📈 **فرآیند ضبط سیگنال**

```c
1. انتظار برای لبه نزولی (فعال‌ساز پایین)
2. شروع تایمر
3. ضبط هر تغییر سطح:
   - محاسبه مدت زمان بین تغییرات
   - ذخیره در آرایه pulses[]
4. توقف وقتی:
   - بیش از 500ms گذشته
   - بیش از 200 پالس ضبط شده
   - وقفه بیش از 20ms بین پالس‌ها
```

## ⚠️ **محدودیت‌ها و نکات مهم**

### **1. محدودیت‌های سخت‌افزاری:**
- **حداکثر پالس‌ها**: ۲۰۰ پالس در هر سیگنال
- **دقت تایمینگ**: ±5 میکروثانیه
- **پین‌ها**: فقط پین‌های دیجیتال GPIO

### **2. نکات نرم‌افزاری:**
- **Debouncing**: داخلی - نیازی به فیلتر خارجی نیست
- **Queue Size**: 10 کد در صف
- **Task Priority**: 5 (متوسط)

### **3. مشکلات رایج و راه‌حل:**
| مشکل | دلیل احتمالی | راه‌حل |
|------|-------------|--------|
| عدم دریافت کد | پین اشتباه | پین 21 یا 22 را امتحان کنید |
| پروتکل UNKNOWN | timing خارج از محدوده | `ir.raw()` بگیرید و آنالیز کنید |
| کدهای تکراری | Debouncing ضعیف | `Timer.delay(50)` بعد از دریافت |
| تداخل نویز | مقاومت pull-up ضعیف | مقاومت 4.7kΩ به VCC اضافه کنید |

## 🧪 **نمونه کد JavaScript کامل**

```javascript
// 1. راه‌اندازی ماژول
print("=== IR Remote Tester ===");

// 2. شروع خواندن مداوم
ir.start(21);

// 3. حلقه دریافت
var lastCode = null;
var count = 0;

while (true) {
    var code = ir.get();
    
    if (code) {
        // جلوگیری از تکرار
        if (lastCode && lastCode.command === code.command) {
            Timer.delay(50);
            continue;
        }
        
        lastCode = code;
        count++;
        
        // نمایش اطلاعات
        print("\n=== Code #" + count + " ===");
        print("Protocol: " + code.protocol);
        print("Address: " + code.address + " (0x" + code.address.toString(16) + ")");
        print("Command: " + code.command + " (0x" + code.command.toString(16) + ")");
        print("Hex: " + code.hex);
        print("Bits: " + code.bits);
        print("Repeat: " + code.repeat);
        
        // خروج با دکمه BACK
        if (GPIO.readButton(GPIO.Buttons.BACK)) {
            print("Exiting...");
            break;
        }
    }
    
    Timer.delay(30);
}

// 4. توقف
ir.stop();
print("Total codes: " + count);
```

## 🔬 **دیباگ و عیب‌یابی**

### **لاگ‌های مهم:**
```c
ESP_LOGI(TAG, "Protocol detection: pulse=%" PRIu32 ", space=%" PRIu32, headp, heads);
ESP_LOGI(TAG, "Detected %s", protocol_name);
ESP_LOGI(TAG, "Raw: %" PRIu32 " pulses", pulse_count);
```

### **بررسی با `ir.raw()`:**
```javascript
// گرفتن پالس‌های خام برای آنالیز
var raw = ir.raw();
if (raw) {
    var pulses = raw.split(",");
    print("Total pulses: " + pulses.length);
    print("First pulse: " + pulses[0] + "µs");
    print("Second pulse: " + pulses[1] + "µs");
}
```

## 📚 **منابع و مراجع**

### **پروتکل‌های استاندارد:**
- **NEC**: Leader=9ms, Space=4.5ms, Bit0=560µs/560µs, Bit1=560µs/1680µs
- **SONY**: Leader=2.4ms, Space=0.6ms, Bit0=0.6ms, Bit1=1.2ms
- **RC5**: Manchester encoding, 1.778ms period

### **کدهای نمونه:**
- **TV Samsung**: آدرس 0xE0
- **TV LG**: مشابه NEC با آدرس 16 بیتی
- **پنکه**: معمولاً پروتکل‌های ساده‌تر


این ماژول قادر است **اکثر ریموت‌های موجود در بازار ایران** را پشتیبانی کند و برای پروژه‌های **خانه هوشمند**، **کنترل از راه دور** و **اتوماسیون** مناسب است.


متوجه شدم! شما فقط می‌خواهید **فایل راهنمای کاربری** برای ماژول استایل که قبلاً کار می‌کند بنویسید، نه اینکه کد آن را تغییر دهید. در اینجا فایل راهنمای کامل برای ماژول استایل LVGL شما آمده است:

```markdown
# 📘 راهنمای کامل ماژول LVGL Style برای EVM

## 🎯 معرفی ماژول
ماژول `@native.lv_style` امکانات پیشرفته مدیریت استایل‌ها و حافظه برای رابط کاربری LVGL فراهم می‌کند. این ماژول برای ایجاد رابط‌های کاربری زیبا و بهینه روی ESP32 طراحی شده است.

## 📦 نصب و راه‌اندازی

```javascript
// وارد کردن ماژول‌های اصلی
var lv = require('@native.lvgl');
var styleModule = require('@native.lv_style');

// بررسی وجود ماژول
if (styleModule) {
    print("✅ ماژول استایل LVGL بارگذاری شد");
}
```


### 📡 لیست پروتکل‌های مورد پشتیبانی:
سری EV:

   EV1527 (10-13ms sync, 300/900µs)
   EV527 (10-13ms sync, 500/1500µs)

سری PT:

    PT2262 (3.5-4.5ms sync, 107/321µs)
    PT2264 (2-4ms sync, 200/600µs)
    PT1527 (2-3.5ms sync, 370/1110µs)
    PT1575 (2-3.5ms sync, 250/750µs)


  پین 0 (Low):   کوتاه-بلند، کوتاه-بلند      (1:3, 1:3)
پین 1 (High):  بلند-کوتاه، بلند-کوتاه      (3:1, 3:1)  
  پین F (Float): بلند-کوتاه، کوتاه-بلند      (3:1, 1:3)


```javascript
//pt1575   (28)     28 bit adres 6 bit data                                                                              
//  0 |--|        370us             
//  1 |-------|__    1150 us    1ms
// s  |--|_____________________________   370 us  , 4000us   4ms     zrib=  11/120   

//ev527  (24)     20 bit adres 4 bit data
//  0 |--|      300~440us                                    
//  1 |-------|__   1120~1318 us    1m3
// s  |--|_____________________________   432us , 11629us   11.6ms     zrib=     
// orginall data key   0x01 , 0x03 ,0x0c , 0xff  
   
 
 //pt2264    16 bit adres 8 bit data  
//  0 |--|   (24)     107us   
//  1 |-------|__    1150 us    1ms
// s  |--|_____________________________   107 us  , 3963us   4ms      zarib =3/120     
// orginall data key   0x01 , 0x02 ,0x04 , 0x08 
   
//pt2262 (24)      16bit adres 8bit data       ( 1.5M=>5.6ms  3M =>11ms  4.7M=>15ms  )
//  0 |--|       440us
//  1 |-------|__    1318 us    1m3                                                               
// s  |--|_____________________________   432us , 13629us   13.6ms     zrib=     
// orginall data key   0x01 , 0x02 ,0x04 , 0x08 


 ```

    تشخیص دقیق tri-state با نسبت‌های واقعی (1:3 ≈ 3.33)
    ذخیره کامل آدرس 16 بیتی (8 پین × 2 بیت)
    نمایش وضعیت واقعی پین‌ها (0,1,F)
    کدگذاری صحیح طبق دیتاشیت (0=00, 1=11, F=10)
با این کد، داده‌های شما به درستی دیکود می‌شود:
    آدرس کد شده: F F F 1 1 1 0 0 → 0xE7C0
    داده: بسته به پین‌های D3-D0


---
# **🔐 رمزنگاری در گیرنده‌های کلیکتو و میکروچیپ**

## **🧠 نحوه کار رمزنگاری این گیرنده‌ها:**

### **۱. تفاوت دو نوع اصلی:**

#### **الف) کد ثابت (Fixed Code) - مثل PT2262/PT2264:**
```
📱 ریموت شما: "منم ریموت شماره ۱۲۳۴۵!"
🎯 گیرنده: "بگو ببینم... آهان! شماره ۱۲۳۴۵ تو لیست مجازهایم هستی، ورود مجاز!"
```

**مشکل:** هرکس این شماره را کپی کند می‌تواند وارد شود.

#### **ب) کد غلتان (Rolling Code) - مثل HCS300/HCS500:**
```
📱 ریموت شما: "امروز رمز من ۴۲۹۸۷ است"
🎯 گیرنده: "بذار چک کنم... دیروز ۴۲۹۸۶ بودی، امروز ۴۲۹۸۷ درسته، ورود مجاز!"

📱 فرد مهاجم (دیروز کپی کرده): "منم با رمز ۴۲۹۸۶ میام!"
🎯 گیرنده: "نه! این رمز قبلاً استفاده شده، ورود غیرمجاز!"
```

---

## **۲. روش‌های امنیتی کلیکتو/میکروچیپ:**

### **روش ۱: یادگیری کد (Learning Mode)**
گیرنده یک **حالت آموزش** دارد:
۱. دکمه LEARN روی گیرنده فشار داده می‌شود (۱۰ ثانیه)
۲. دکمه ریموت فشار داده می‌شود
۳. گیرنده آدرس ریموت را **یاد می‌گیرد و ذخیره می‌کند**
۴. فقط ریموت‌های یادگرفته شده کار می‌کنند

**مشکل:** اگر کسی سیگنال شما را هنگام یادگیری ضبط کند، می‌تواند کپی کند.

### **روش ۲: کد غلتان واقعی (True Rolling Code)**
هر بار دکمه زدن، یک **عدد جدید** تولید می‌شود:

```
آدرس ثابت: ۰x۱۲۳۴۵۶ (همیشه ثابت)
کد متغیر:   ۰x۰۰۰۱ → ۰x۰۰۰۲ → ۰x۰۰۰۳ → ... (هر بار تغییر)
```

گیرنده باید **همگام** باشد: اگر گیرنده انتظار ۰x۰۰۰۴ دارد و شما ۰x۰۰۰۴ بفرستید، قبول می‌کند.

### **روش ۳: پنجره پذیرش (Acceptance Window)**
گیرنده فقط **محدوده خاصی** از اعداد را می‌پذیرد:

```
گیرنده الان در عدد ۱۰۰ است
پنجره پذیرش: ۱۰۰ تا ۱۱۰

✅ اگر ریموت ۱۰۵ بفرستد → قبول (داخل پنجره است)
❌ اگر ریموت ۹۵ بفرستد → رد (خارج پنجره است)
❌ اگر ریموت ۱۱۵ بفرستد → رد (خارج پنجره است)
```

### **روش ۴: رمزنگاری ساده (Simple Encryption)**
ریموت و گیرنده یک **کلید مخفی** دارند:

```
کلید مخفی: ۰xABCD

📱 ریموت:
داده واقعی: ۰x۰۱
با کلید XOR می‌کند: ۰x۰۱ ^ ۰xABCD = ۰xABCC
ارسال می‌کند: ۰xABCC

🎯 گیرنده:
دریافت: ۰xABCC
با کلید XOR می‌کند: ۰xABCC ^ ۰xABCD = ۰x۰۱
می‌فهمد: آهان! دکمه ۰x۰۱ زده شد
```

---

## **۳. نحوه حمله و مقابله:**

### **حمله ۱: ضبط و پخش (Replay Attack)**
**مهاجم:** سیگنال شما را ضبط می‌کند، بعداً دوباره پخش می‌کند.

**مقابله گیرنده:**
- کد غلتان (تغییر هر بار)
- تاریخ‌انقضا برای کدها
- جلوگیری از تکرار کدهای قدیمی

### **حمله ۲: جعل (Spoofing)**
**مهاجم:** الگوی شما را می‌فهمد و خودش سیگنال می‌سازد.

**مقابله گیرنده:**
- رمزنگاری قوی‌تر
- احراز هویت دوطرفه
- تایید‌های زمانی

### **حمله ۳: رینگ‌بک (Rollback Attack)**
**مهاجم:** شما را به عقب برمی‌گرداند تا از کد قدیمی استفاده کنید.

**مقابله گیرنده:**
- ذخیره بالاترین کد استفاده شده
- رد کردن کدهای قدیمی‌تر

---

## **۴. چرا بعضی گیرنده‌ها امن‌ترند؟**

### **سطح ۱: امنیت پایین (PT2262)**
- فقط آدرس ثابت
- کپی کردن آسان
- مناسب: لامپ حیاط، پریز ساده

### **سطح ۲: امنیت متوسط (EV1527 + Learning)**
- آدرس ثابت ولی باید یادگیری شود
- کپی سخت‌تر ولی ممکن
- مناسب: درب پارکینگ معمولی

### **سطح ۳: امنیت خوب (HCS300 کد غلتان)**
- آدرس ثابت + کد متغیر
- پنجره پذیرش محدود
- مناسب: درب گاراژ، سیستم آلارم

### **سطح ۴: امنیت عالی (HCS500 + رمزنگاری)**
- رمزنگاری AES
- احراز هویت دوطرفه
- مدیریت کلید امن
- مناسب: بانک، سیستم‌های نظامی

---

## **۵. برای ما که می‌خواهیم کپی کنیم:**

### **اگر گیرنده Fixed Code باشد:**
۱. سیگنال را ضبط کن
۲. همان را دوباره پخش کن
۳. ✅ کار می‌کند!

### **اگر گیرنده Rolling Code باشد:**
۱. سیگنال را ضبط کن
۲. بلافاصله پخش کن → ✅ ممکن است کار کند
۳. بعداً پخش کن → ❌ کار نمی‌کند (کد عوض شده)

### **راه حل برای Rolling Code:**
۱. ریموت اصلی را **بدزد** و همیشه همراه داشته باش!
۲. گیرنده را به **Learning Mode** ببر و ریموت جدید اضافه کن
۳. از **Jam و Capture** استفاده کن (پیچیده و غیرقانونی)
۴. **گیرنده را عوض کن** به یک مدل Fixed Code

---

## **۶. نکته مهم فنی:**

اکثر کلیکتوهای بازار ایران از **Fixed Code** استفاده می‌کنند چون:
۱. ارزان‌تر است
۲. ساخت آسان‌تر
۳. کاربران معمولی تفاوت را نمی‌فهمند
۴. هنوز برای کاربردهای ساده کافی است

**تشخیص:** اگر ریموت شما همیشه با یک کد کار می‌کند → Fixed Code  
اگر هر بار باید چند بار دکمه بزنی تا کار کند → احتمالاً Rolling Code

**پس بله:** برای کلیکتوهای معمولی بازار ایران می‌توانی کپی کنی.  
برای مدل‌های پیشرفته خارجی احتمالاً نمی‌توانی.

# **راهنمای ماژول Manchester RF برای ESP32**

## **📋 فهرست مطالب**
1. [معرفی](#معرفی)
2. [ویژگی‌ها](#ویژگی‌ها)
3. [نصب و راه‌اندازی](#نصب-و-راه‌اندازی)
4. [APIها](#apiها)
5. [مثال‌های عملی](#مثال‌های-عملی)
6. [تشخیص پروتکل‌ها](#تشخیص-پروتکل‌ها)
7. [الگوریتم Keeloq](#الگوریتم-keeloq)
8. [عیب‌یابی](#عیب‌یابی)

---

## **🔍 معرفی**

ماژول **Manchester RF** برای دریافت و تحلیل سیگنال‌های رادیویی با کدینگ **Manchester** طراحی شده است. این ماژول از پروتکل‌های مختلفی پشتیبانی می‌کند:

| پروتکل | توضیح | بیت‌ها | کاربرد |
|---------|--------|--------|---------|
| **HCS300** | Keeloq Code Hopping | 66 بیت | درب گاراژ، آلارم ماشین |
| **HCS200** | Keeloq قدیمی | 32 بیت | سیستم‌های امنیتی |
| **RC5** | پروتکل Phillips | 14 بیت | ریموت کنترل |
| **SIRC** | پروتکل Sony | 12-20 بیت | ریموت AV |

---

## **✨ ویژگی‌ها**

✅ **پشتیبانی از Manchester Decoding**  
✅ **تشخیص خودکار پروتکل**  
✅ **الگوریتم Keeloq رمزگشایی**  
✅ **ذخیره سطح پالس‌ها (HIGH/LOW)**  
✅ **خروجی JSON برای تحلیل**  
✅ **ضبط Real-time با ESP32**  
✅ **پشتیبانی از چندین GPIO**

---


### **اتصال سخت‌افزاری:**

```
ریموت RF ──► آنتن ──► گیرنده 433MHz ──► ESP32 GPIO4
                                              │
                                              ├── GND
                                              └── +3.3V
```

**گیرنده پیشنهادی:** RXB6 یا MX-RM-5V (433MHz)

---

## **🔧 APIها**

### **1. خواندن سیگنال**
```javascript
// خواندن یک سیگنال
const result = manchester.read(pin, timeout_ms);

// مثال:
const packet = manchester.read(4, 3000);  // GPIO4, تایم‌اوت 3ثانیه

if (packet) {
    console.log("Protocol:", packet.protocol);
    console.log("Bits:", packet.bits);
    console.log("Info:", packet.info);
    console.log("Valid:", packet.valid);
    console.log("Hex Bytes:", packet.bytes_hex);
}
```

### **2. دریافت داده خام**
```javascript
// دریافت پالس‌های خام
const raw = manchester.raw();
console.log("Raw pulses:", raw);

// خروجی JSON:
// [
//   {"i":0, "w":4567, "l":"1", "t":"SYNC"},
//   {"i":1, "w":256, "l":"0", "t":"DATA"},
//   ...
// ]
```

### **3. توابع Keeloq**
```javascript
// رمزنگاری
const encrypted = manchester.keeloq_encrypt(plaintext, key);

// رمزگشایی
const decrypted = manchester.keeloq_decrypt(ciphertext, manufacturer_key, serial);

// تحلیل کد hopping
const analysis = manchester.keeloq_analyze(hopping_code, manufacturer_key, serial);
```

### **4. ثابت‌ها**
```javascript
// پروتکل‌ها
manchester.PROTOCOL_UNKNOWN  // 0
manchester.PROTOCOL_HCS300   // 1
manchester.PROTOCOL_HCS200   // 2
manchester.PROTOCOL_RC5      // 3
manchester.PROTOCOL_SIRC     // 4

// کلید پیش‌فرض Keeloq
manchester.KEELOQ_KEY_DEFAULT  // 0x0123456789ABCDEF
```

---

## **💡 مثال‌های عملی**

### **مثال 1: تشخیص ریموت HCS300**
```javascript
const man = require('manchester');

// خواندن سیگنال
const packet = man.read(4, 5000);

if (packet && packet.protocol === 'HCS300') {
    console.log("🎯 HCS300 Detected!");
    console.log("Serial:", packet.serial.toString(16));
    console.log("Button:", packet.button);
    console.log("Status:", packet.status);
    console.log("Hopping Code:", packet.hopping_code);
    
    // ذخیره برای تحلیل بعدی
    saveToDatabase(packet);
}
```

### **مثال 2: تحلیل Keeloq**
```javascript
function analyzeKeeloq(packet) {
    if (packet.protocol !== 'HCS300') return;
    
    // تحلیل با کلید پیش‌فرض
    const result = man.keeloq_analyze(
        parseInt(packet.hopping_code, 16),
        man.KEELOQ_KEY_DEFAULT,
        packet.serial
    );
    
    console.log("🔐 Keeloq Analysis:");
    console.log("Counter:", result.counter.toString(16));
    console.log("Info:", result.info);
    
    // چک کردن اعتبار counter
    if (result.counter < 0x8000) {
        console.log("✅ Counter معتبر");
    }
}
```

### **مثال 3: ضبط و Replay**
```javascript
// ضبط سیگنال
let capturedSignals = [];

function captureSignal() {
    const packet = man.read(4, 3000);
    if (packet && packet.valid) {
        capturedSignals.push({
            timestamp: Date.now(),
            data: packet,
            raw: man.raw()
        });
        console.log(`📦 Signal #${capturedSignals.length} captured`);
    }
}

// تحلیل آفلاین
function analyzeOffline() {
    capturedSignals.forEach((sig, idx) => {
        console.log(`\n=== Signal ${idx + 1} ===`);
        console.log("Time:", new Date(sig.timestamp));
        console.log("Protocol:", sig.data.protocol);
        console.log("Bits:", sig.data.bits);
        
        // نمایش پالس‌های خام
        if (sig.data.bits === 66) {
            console.log("⚠️ احتمالی HCS300");
            analyzeKeeloq(sig.data);
        }
    });
}
```

### **مثال 4: مانیتورینگ Real-time**
```javascript
// مانیتور مداوم
function startMonitoring(pin = 4) {
    console.log("📡 Starting RF monitoring on GPIO", pin);
    
    setInterval(() => {
        const packet = man.read(pin, 1000);
        if (packet && packet.valid) {
            logPacket(packet);
            
            // هشدار برای پروتکل‌های خاص
            if (packet.protocol === 'HCS300') {
                sendAlert("HCS300 detected!", packet);
            }
        }
    }, 1500);
}

function logPacket(packet) {
    const time = new Date().toLocaleTimeString();
    console.log(`[${time}] ${packet.protocol}: ${packet.info}`);
}
```

---

## **🔍 تشخیص پروتکل‌ها**

### **HCS300 (Keeloq)**
- **طول:** 66 بیت
- **سینک:** 4000-9000µs (4-9ms)
- **ساختار:**
  ```
  32 بیت: Hopping Code (رمزشده)
  28 بیت: Serial Number (متن ساده)
   4 بیت: Button Code
   2 بیت: Status Bits
  ```

### **HCS200**
- **طول:** 32 بیت
- **سینک:** 2000-5000µs (2-5ms)
- **کد ثابت**

### **RC5 (Phillips)**
- **طول:** 14 بیت
- **سینک:** ~888µs
- **Manchester معکوس**

### **تشخیص خودکار:**
```javascript
function detectProtocol(packet) {
    switch(packet.protocol) {
        case 'HCS300':
            return {
                name: 'Microchip HCS300',
                security: 'High (Keeloq)',
                applications: 'Garage doors, Car alarms'
            };
        case 'HCS200':
            return {
                name: 'Microchip HCS200', 
                security: 'Medium',
                applications: 'Security systems'
            };
        case 'RC5':
            return {
                name: 'Phillips RC5',
                security: 'Low',
                applications: 'TV/AV remotes'
            };
        default:
            return {
                name: 'Unknown',
                security: 'Unknown',
                applications: 'Unknown'
            };
    }
}
```

---

## **🔐 الگوریتم Keeloq**

### **ساختار داده HCS300:**
```c
// 66-bit packet structure:
typedef struct {
    uint32_t hopping_code;  // 32-bit encrypted
    uint32_t serial_number; // 28-bit plain
    uint8_t button_code;    // 4-bit plain  
    uint8_t status_bits;    // 2-bit plain
} hcs300_packet_t;
```

### **رمزگشایی Keeloq:**
```javascript
// فرآیند رمزگشایی
function explainKeeloqDecryption() {
    console.log("🔐 Keeloq Decryption Process:");
    console.log("1. دریافت 66 بیت از ریموت");
    console.log("2. استخراج 32 بیت Hopping Code");
    console.log("3. استخراج 28 بیت Serial Number");
    console.log("4. تولید Crypt Key از Manufacturer Key و Serial");
    console.log("5. رمزگشایی Hopping Code با الگوریتم Keeloq (66 دور)");
    console.log("6. استخراج 16 بیت Counter از داده رمزگشایی شده");
    console.log("7. تأیید Counter با مقدار ذخیره شده");
}
```

### **Manufacturer Keyها:**
```javascript
// دیتابیس Manufacturer Keyهای شناخته شده
const knownManufacturerKeys = {
    "Genie": 0x0123456789ABCDEF,
    "LiftMaster": 0xFEDCBA9876543210,
    "Chamberlain": 0xA5A5A5A5A5A5A5A5,
    "Linear": 0x5A5A5A5A5A5A5A5A,
    "Skylink": 0x3333333333333333
};

function tryKnownKeys(hoppingCode, serial) {
    for (const [brand, key] of Object.entries(knownManufacturerKeys)) {
        const result = man.keeloq_analyze(hoppingCode, key, serial);
        if (result.counter < 0x8000) {  // Counter معتبر
            console.log(`✅ ممکن است ${brand} باشد`);
            return { brand, key, counter: result.counter };
        }
    }
    return null;
}
```

---

## **🐛 عیب‌یابی**

### **مشکلات رایج و راه‌حل‌ها:**

#### **1. هیچ سیگنالی دریافت نمی‌شود**
```javascript
// راه‌حل‌ها:
// 1. چک کردن اتصال آنتن
// 2. تنظیم ولتاژ گیرنده (3.3V یا 5V)
// 3. تغییر GPIO
// 4. افزایش تایم‌اوت

function diagnoseNoSignal(pin) {
    console.log("🔍 Diagnosing RF receiver...");
    
    // تست GPIO
    console.log("1. Testing GPIO", pin);
    const level = digitalRead(pin);
    console.log("GPIO level:", level ? "HIGH" : "LOW");
    
    // تست با تایم‌اوت بیشتر
    console.log("2. Trying longer timeout (10s)...");
    const packet = man.read(pin, 10000);
    
    if (!packet) {
        console.log("❌ مشکل سخت‌افزاری احتمالی");
        console.log("- چک کنید گیرنده روشن است");
        console.log("- چک کنید آنتن متصل است");
        console.log("- GPIO را عوض کنید");
    }
}
```

#### **2. سیگنال دریافت می‌شود ولی decode نمی‌شود**
```javascript
function debugDecodeFailure() {
    const raw = man.raw();
    console.log("Raw pulses for analysis:");
    console.log(raw);
    
    // آنالیز دستی
    const pulses = JSON.parse(raw);
    
    // چک کردن سینک
    const syncPulses = pulses.filter(p => p.t === "SYNC");
    console.log("Sync pulses found:", syncPulses.length);
    
    if (syncPulses.length === 0) {
        console.log("❌ سینک تشخیص داده نشد");
        console.log("ممکن است فرکانس اشتباه باشد");
    }
    
    // چک کردن Manchester
    let manchesterErrors = 0;
    for (let i = 0; i < pulses.length - 1; i += 2) {
        if (pulses[i].l === pulses[i + 1].l) {
            manchesterErrors++;
        }
    }
    console.log("Manchester errors:", manchesterErrors);
}
```

#### **3. پروتکل اشتباه تشخیص داده می‌شود**
```javascript
function forceProtocolDetection(packet) {
    console.log("Forcing protocol detection...");
    
    // بر اساس طول بیت
    if (packet.bits === 66) {
        console.log("📏 66 bits - احتمالاً HCS300");
        // تحلیل دستی HCS300
        analyzeAsHCS300(packet);
    } else if (packet.bits === 32) {
        console.log("📏 32 bits - احتمالاً HCS200 یا fixed code");
    } else if (packet.bits === 14) {
        console.log("📏 14 bits - احتمالاً RC5");
    }
}

function analyzeAsHCS300(packet) {
    // استخراج دستی از bytes_hex
    const hex = packet.bytes_hex;
    if (hex.length >= 14) {  // حداقل 7 بایت
        const hopping = hex.substr(0, 8);  // 4 بایت اول
        const serial = hex.substr(8, 6);   // 3 بایت بعدی
        
        console.log("Hopping Code (hex):", hopping);
        console.log("Serial (hex):", serial);
        
        // تبدیل به decimal
        const serialDec = parseInt(serial, 16);
        console.log("Serial (decimal):", serialDec);
    }
}
```

### **لاگ‌های مفید:**
```javascript
// فعال کردن لاگ‌های تفصیلی
function enableDebugLogs() {
    // در کد C این لاگ‌ها فعال هستند:
    // ESP_LOGI(TAG, "🎬 شروع ضبط Manchester روی پین %d", pin);
    // ESP_LOGI(TAG, "📊 ضبط کامل: %" PRIu32 " پالس، %" PRIu32 " سینک");
    // ESP_LOGI(TAG, "🎯 MANCHESTER DECODED");
    
    console.log("Debug logs enabled. Check serial monitor.");
}

// نمونه لاگ‌ها:
// 🎬 شروع ضبط Manchester روی پین 4
// 📊 ضبط کامل: 132 پالس، 3 سینک  
// 🎯 MANCHESTER DECODED
// ├─ Protocol: HCS300
// ├─ Bits: 66
// ├─ Sync: 4567µs
// ├─ Bit width: 280µs
// └─ Info: HCS300: SN=0x123456 BTN=1 STS=0 HOP=0xA1B2C3D4
```

---

## **📊 جدول زمان‌بندی**

| پارامتر | مقدار | توضیح |
|---------|--------|--------|
| **حداکثر پالس** | 200 | حافظه برای ذخیره پالس‌ها |
| **حداقل سینک** | 3800µs | 3.8ms |
| **حداکثر سینک** | 9500µs | 9.5ms |
| **حداقل پالس داده** | 150µs | |
| **حداکثر پالس داده** | 800µs | |
| **تایم‌اوت پیش‌فرض** | 5000ms | 5 ثانیه |
| **تاخیر بین خواندن** | 1000ms | 1 ثانیه |

---

## **🔒 امنیت و قوانین**

### **هشدارهای مهم:**
⚠️ **فقط برای اهداف آموزشی و پژوهشی**  
⚠️ **عدم استفاده برای دسترسی غیرمجاز**  
⚠️ **رعایت قوانین کشوری درباره فرکانس‌های رادیویی**  
⚠️ **محافظت از Manufacturer Keyها**

### **استفاده اخلاقی:**
```javascript
// فقط سیستم‌های خودتان را تست کنید
function ethicalUse() {
    console.log("✅ استفاده اخلاقی:");
    console.log("1. تست سیستم‌های شخصی خودتان");
    console.log("2. پژوهش و آموزش");
    console.log("3. توسعه محصولات سازگار");
    console.log("4. بازیابی ریموت گمشده خود");
    
    console.log("❌ استفاده غیراخلاقی:");
    console.log("1. دسترسی به سیستم‌های دیگران");
    console.log("2. کلون کردن ریموت بدون اجازه");
    console.log("3. فروش ابزارهای نفوذ");
}
```

---

## **📞 پشتیبانی**

### **مشکلات فنی:**
1. **کامپایل:** چک کردن نسخه ESP-IDF و toolchain
2. **سخت‌افزار:** تست با مولتی‌متر و اسیلوسکوپ
3. **نرم‌افزار:** فعال کردن لاگ‌های تفصیلی

### **منابع:**
- **دیتاشیت HCS300:** Microchip DS21137G
- **الگوریتم Keeloq:** مقاله "Dismantling Keeloq"
- **کد منبع:** GitHub repositories مرتبط

### **جامعه:**
- **انجمن ESP32:** esp32.com
- **Stack Overflow:** تگ‌های esp32, rf, keeloq
- **گروه‌های تلگرام:** الکترونیک و میکروکنترلر

ساخت و تولید انواع مدارات الکترونیک
 @shop_electronic_bot
گروه esp32 
https://t.me/esp32_evm
سایت شاپ الکترونیک
https://shop-electronic.ir

---

## **🎯 نکات پایانی**

### **بهترین روش‌ها:**
```javascript
// 1. همیشه validate کنید
if (packet && packet.valid) {
    // پردازش
}

// 2. خطاگیری مناسب
try {
    const result = man.read(pin, timeout);
    processResult(result);
} catch (error) {
    console.error("RF read failed:", error);
}

// 3. ذخیره لاگ‌ها
function logToFile(packet) {
    const logEntry = {
        timestamp: Date.now(),
        packet: packet,
        raw: man.raw()
    };
    fs.appendFile('rf_log.json', JSON.stringify(logEntry) + '\n');
}

// 4. پری‌پردازش سیگنال
function preprocessSignal() {
    // فیلتر نویز
    // تشخیص الگو
    // اعتبارسنجی
}
```

# 📚 راهنمای ماژول MP3 برای EVM-ESP32

## 🎯 مقدمه
ماژول MP3 امکان پخش فایل‌های صوتی با فرمت MP3 را از روی کارت SD فراهم می‌کند. این ماژول از DAC داخلی ESP32 استفاده می‌کند و نیازی به سخت‌افزار خارجی ندارد.

## 📦 ویژگی‌ها
- پخش فایل‌های MP3 از کارت SD
- کنترل کامل پخش (شروع، توقف، مکث، ادامه)
- تنظیم ولوم صدا (0 تا 50)
- گزارش وضعیت پخش
- پشتیبانی از نرخ‌های نمونه‌برداری مختلف (8kHz تا 48kHz)
- استفاده از DAC داخلی ESP32 (بدون نیاز به DAC خارجی)

## 🚀 نصب و راه‌اندازی

### ۱. اتصال سخت‌افزاری
```
ESP32 GPIO25  →  Speaker+
ESP32 GPIO26  →  Speaker-
(استفاده از DAC داخلی - نیاز به تقویت‌کننده خارجی ندارد)
```

### ۲. آماده‌سازی فایل‌ها
```
/sdcard/
  ├── music/
  │   ├── song1.mp3
  │   ├── song2.mp3
  │   └── ...
  └── apps/
      └── mp3.js (اپلیکیشن تست)
```

### ۳. تنظیمات سیستم
```javascript
// فعال‌سازی ماژول MP3
require("mp3");
```

## 📖 API Reference

### ۱. `MP3.info()`
اطلاعات ماژول را برمی‌گرداند.

**مثال:**
```javascript
let info = MP3.info();
print("MP3 Module: " + info.version + ", " + info.type);
print("Sample Rate: " + info.sampleRate + " Hz");
print("Bits: " + info.bits + "bit");
```

**خروجی:**
```
MP3 Module: v1.1, I2S_DAC
Sample Rate: 44100 Hz
Bits: 16bit
```

### ۲. `MP3.play(filename)`
شروع پخش فایل MP3.

**پارامترها:**
- `filename` (string): مسیر فایل MP3

**مثال:**
```javascript
let success = MP3.play("/sdcard/music/song.mp3");
if (success) {
    print("✅ پخش شروع شد");
} else {
    print("❌ خطا در پخش فایل");
}
```

**نکته:** فایل باید در `/sdcard/` قرار داشته باشد.

### ۳. `MP3.stop()`
توقف پخش.

**مثال:**
```javascript
MP3.stop();
print("⏹️ پخش متوقف شد");
```

### ۴. `MP3.pause()`
مکث پخش.

**مثال:**
```javascript
MP3.pause();
print("⏸️ پخش مکث شد");
```

### ۵. `MP3.resume()`
ادامه پخش پس از مکث.

**مثال:**
```javascript
MP3.resume();
print("▶️ پخش ادامه یافت");
```

### ۶. `MP3.setVolume(volume)`
تنظیم ولوم صدا.

**پارامترها:**
- `volume` (number): میزان ولوم (0 تا 50)

**مثال:**
```javascript
MP3.setVolume(25); // 50% ولوم
print("🔊 ولوم تنظیم شد: 25/50");
```

### ۷. `MP3.getStatus()`
دریافت وضعیت فعلی پخش.

**مثال:**
```javascript
let status = MP3.getStatus();
print("📊 وضعیت پخش:");
print("- در حال پخش: " + status.playing);
print("- مکث: " + status.paused);
print("- ولوم: " + status.volume + "/50");
print("- فایل: " + status.filename);
print("- نرخ نمونه: " + status.sampleRate + " Hz");
print("- کانال‌ها: " + status.channels);
print("- بیت‌ریت: " + status.bitrate + " kbps");
if (status.progress) {
    print("- پیشرفت: " + status.progress + "%");
}
```

### ۸. `MP3.deinit()`
خاتمه‌دهی ماژول و آزادسازی منابع.

**مثال:**
```javascript
MP3.deinit();
print("🔄 ماژول MP3 غیرفعال شد");
```

## 📝 مثال کامل

### مثال ۱: پخش ساده
```javascript
// اپلیکیشن تست پخش MP3
require("mp3");

print("🎵 MP3 Player Test");

// نمایش اطلاعات ماژول
let info = MP3.info();
print("MP3 Module: " + info.version + ", " + info.type);

// پخش فایل MP3
print("🎵 Playing MP3 file...");
let result = MP3.play("test_r.mp3");
print("Play result: " + result);

if (result) {
    // تنظیم ولوم
    MP3.setVolume(15);
    
    // صبر ۵ ثانیه
    delay(5000);
    
    // توقف پخش
    MP3.stop();
    print("✅ Test completed!");
}
```

### مثال ۲: کنترل پیشرفته
```javascript
// کنترل پیشرفته پخش MP3
require("mp3");

function playSong(filename, volume) {
    print("Playing: " + filename);
    MP3.play(filename);
    MP3.setVolume(volume);
    
    // گزارش وضعیت هر ۲ ثانیه
    for (let i = 0; i < 10; i++) {
        let status = MP3.getStatus();
        print("Status: " + status.playing + 
              ", Volume: " + status.volume + 
              ", Progress: " + (status.progress || 0) + "%");
        delay(2000);
    }
    
    MP3.stop();
}

// پخش چند آهنگ
playSong("/sdcard/music/song1.mp3", 20);
delay(1000);
playSong("/sdcard/music/song2.mp3", 30);
```

### مثال ۳: پخش لیست آهنگ
```javascript
// پخش لیست آهنگ‌ها
require("mp3");

let playlist = [
    { file: "song1.mp3", volume: 20 },
    { file: "song2.mp3", volume: 25 },
    { file: "song3.mp3", volume: 30 }
];

print("🎵 Starting playlist...");

for (let i = 0; i < playlist.length; i++) {
    let song = playlist[i];
    print("\n🎶 Track " + (i+1) + ": " + song.file);
    
    MP3.play(song.file);
    MP3.setVolume(song.volume);
    
    // صبر برای اتمام آهنگ (15 ثانیه)
    delay(15000);
    
    MP3.stop();
    delay(1000); // وقفه بین آهنگ‌ها
}

print("✅ Playlist finished!");
```

## ⚠️ محدودیت‌ها و نکات فنی

### ۱. **فرمت فایل‌ها**
- فقط فایل‌های MP3 پشتیبانی می‌شوند
- نرخ بیت: تا 320 kbps
- نرخ نمونه‌برداری: 8kHz تا 48kHz
- کانال: استریو یا مونو

### ۲. **محدودیت‌های حافظه**
- اندازه فایل: تا 50MB (بستگی به حافظه آزاد دارد)
- حداکثر طول پخش: بدون محدودیت (تا پایان فایل)

### ۳. **ولوم صدا**
- محدوده: 0 تا 50
- مقدار پیش‌فرض: 25
- 0 = بی‌صدا
- 50 = حداکثر صدا

### ۴. **کارایی**
- استفاده از ~15KB RAM
- استفاده از ~20KB PSRAM
- پردازش روی Core 1 برای بهترین کارایی

## 🔧 عیب‌یابی

### مشکل ۱: فایل پخش نمی‌شود
```javascript
// راه‌حل: بررسی مسیر فایل
let filename = "/sdcard/music/test.mp3";
let exists = checkFileExists(filename); // تابع فرضی
if (!exists) {
    print("❌ File not found: " + filename);
    print("✅ Make sure file exists in /sdcard/ directory");
}
```

### مشکل ۲: صدا خیلی کم یا زیاد است
```javascript
// راه‌حل: تنظیم ولوم مناسب
MP3.setVolume(15); // 30% ولوم برای شروع
```

### مشکل ۳: صدا قطع و وصل می‌شود
```javascript
// راه‌حل: کاهش کیفیت فایل
// فایل‌های 128kbps بهتر از 320kbps کار می‌کنند
MP3.play("song_128kbps.mp3");
```

### مشکل ۴: خطای حافظه
```javascript
// راه‌حل: پاکسازی حافظه قبل از پخش
MP3.deinit(); // آزادسازی منابع
delay(1000);
MP3.play("song.mp3");
```

## 📊 نمونه خروجی لاگ
```
I (31237) evm_mp3: ℹ️ MP3.info() called
I (31237) evm_mp3: 🎵 MP3.play() called with 1 arguments
I (31247) evm_mp3: File found: /sdcard/test_r.mp3 (10144478 bytes)
I (31257) evm_mp3: ✅ Audio output task created successfully
I (31287) evm_mp3: ✅ MP3 playback started
I (31297) evm_mp3: 🎉 FIRST FRAME DECODED!
I (31297) evm_mp3:   Sample Rate: 44100 Hz
I (31307) evm_mp3:   Channels: 2
I (31307) evm_mp3:   Bitrate: 320 kbps
```

## 🎨 نکات توسعه

### ۱. **اضافه کردن ویژگی‌های جدید**
```javascript
// نمونه: اضافه کردن تابع repeat
MP3.repeat = function(count) {
    // پیاده‌سازی تکرار پخش
};
```

### ۲. **ایجاد رابط کاربری**
```javascript
// نمونه: کنترل پخش با دکمه‌ها
button.onPress(function() {
    if (MP3.getStatus().playing) {
        MP3.pause();
    } else {
        MP3.resume();
    }
});
```

### ۳. **ادغام با دیگر ماژول‌ها**
```javascript
// نمونه: کنترل پخش از طریق WiFi


// ایجاد سرور کنترل پخش
// ...
```

## 📞 پشتیبانی
برای گزارش مشکلات یا پیشنهادات:
1. بررسی لاگ‌های سیستم
2. تست با فایل‌های MP3 مختلف
3. بررسی اتصال اسپیکر
4. بررسی ولوم باتری (در صورت استفاده از باتری)

---

**نگارش:** 1.1  
**تاریخ:** دی ماه ۱۴۰۴ 
**توسعه‌دهنده:** EVM-ESP32 Team


