TARGET = convert-to-gray
OBJS = main.o

CFLAGS = -Og -Wall -Wextra
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti

LIBS = -lz -ljpeg -lpng -lleptonica

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = convert-to-gray

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
