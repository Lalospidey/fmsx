ifndef Ps4Sdk
ifdef ps4sdk
Ps4Sdk := $(ps4sdk)
endif
ifdef PS4SDK
Ps4Sdk := $(PS4SDK)
endif
ifndef Ps4Sdk
$(error Neither PS4SDK, Ps4Sdk nor ps4sdk set)
endif
endif

keepelf = True
target ?= ps4_elf
TargetFile=msxorbis.elf
#need to add this flags
#-Wl,-T script.ld

###################################

Libraries := -ldebugnet -lps4link -lelfloader -lorbisKeyboard -lorbis2d -lpng -lz -lorbisPad -lorbisAudio -lmod -lorbisFileBrowser -lorbisXbmFont -lSceNet_stub -lSceAudioOut_stub -lSceVideoOut_stub -lSceSystemService_stub  -lSceUserService_stub -lSceGnmDriver_stub -lScePad_stub -lSceLibcInternal_stub -lSceIme_stub -lSceSysmodule_stub

include $(Ps4Sdk)/make/ps4sdk.mk

CompilerFlags += -DFMSX -DALTSOUND -DORBIS -DLSB_FIRST -DNO_WAVE_INTERPOLATION -DBPP32 -DBPS16 -DNARROW

IncludePath += -I./source/EMULIB -I./source/EMULIB/Orbis -I./source/Z80 -I./source/fMSX -I./source/fMSX/Orbis -I./source/fMSX/msxaudio -I./source/fMSX/msxmusic 

