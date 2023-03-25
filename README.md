# Thumby with Pico SDK
This is a test / demo project for using TinyCircuits' Thumby and its peripherals
with the Raspberry Pico SDK only.

The main art has been to re-interpret the ssd1306 OLED driver from
[their Arduino library](https://github.com/TinyCircuits/TinyCircuits-Thumby-Lib)
into Pico SDK terms to get it booting.

The big advantage of using the Pico SDK is that it lends itself well to writing
bigger projects in plain C.

The text writing and fonts are a bit of an extra over a minimal demo.
