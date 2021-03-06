/*
 * fMSX orbis launcher   for PlayStation 4 
 * Copyright (C) 2015,2016,2017 Antonio Jose Ramos Marquez (aka bigboss) @psxdev on twitter
 * Repository https://github.com/psxdev/fmsx
 */
#include <stdio.h>
#include <stdlib.h>

#include <kernel.h>
#include <systemservice.h>
#include <orbis2d.h>
#include <orbisPad.h>
#include <orbisAudio.h>
#include <modplayer.h>
#include <ps4link.h>
#include <orbisKeyboard.h>
#include <debugnet.h>
#include <orbisFileBrowser.h>
#include "menu.h"
#include "browser.h"

typedef struct OrbisGlobalConf
{
	Orbis2dConfig *conf;
	OrbisPadConfig *confPad;
	OrbisAudioConfig *confAudio;
	OrbisKeyboardConfig *confKeyboard;
	ps4LinkConfiguration *confLink;
	int orbisLinkFlag;
}OrbisGlobalConf;

OrbisGlobalConf *myConf;


int x=1280/2;
int y=720/2;
int w=1280/64;
int h=1280/64;
int step=10;


int64_t flipArg=0;
int R,G,B;
uint32_t color=0x80ff0000;
int flag=0;
//int closeMenu=0;
Orbis2dConfig *conf;
OrbisPadConfig *confPad;

//extern char browserBackground[];
//extern char settingsBackground[];
//extern char creditsBackground[];
//extern char folder_icon[];
//extern char file_icon[];
Orbis2dTexture *browserTexture=NULL;
Orbis2dTexture *folderTexture=NULL;
Orbis2dTexture *fileTexture=NULL;

Orbis2dTexture *settingsTexture=NULL;
Orbis2dTexture *creditsTexture=NULL;

int col=0;
void finishApp()
{
	orbis2dFinish();
	orbisAudioFinish();
	orbisKeyboardFinish();
	orbisPadFinish();
	ps4LinkFinish();
		
}
void initTextures()
{
	browserTexture=orbis2dLoadPngFromHost_v2(BROWSERBACKGROUND_FILE_PATH);
	//creditsTexture=orbis2dLoadPngFromHost_v2(CREDITS_FILE_PATH);
	settingsTexture=orbis2dLoadPngFromHost_v2(SETTINGS_FILE_PATH);
	folderTexture=orbis2dLoadPngFromHost_v2(FOLDER_ICON_PATH);
	fileTexture=orbis2dLoadPngFromHost_v2(FILE_ICON_PATH);
	creditsTexture=orbis2dLoadPngFromHost_v2(CREDITS_FILE_PATH);
	if(!creditsTexture)
	{
		debugNetPrintf(DEBUG,"credit chungo\n");
		
	}
	else
	{
		debugNetPrintf(DEBUG,"credit bien\n");
		
	}
}

 

void initApp()
{
	int ret;

	debugNetPrintf(DEBUG,"[PS4LINK] Initialized and connected from pc/mac ready to receive commands\n");
	
	orbisFileBrowserInit("host0:GAMES");
	
	//hide playroom splash
	
	sceSystemServiceHideSplashScreen();
	
	
	ret=orbisPadInitWithConf(myConf->confPad);
	
	if(ret==1)
	{
		
	
		confPad=orbisPadGetConf();
		ret=orbis2dInitWithConf(myConf->conf);
		if(ret==1)
		{
			conf=orbis2dGetConf();
			flag=1;
			ret=orbisAudioInitWithConf(myConf->confAudio);
			if(ret==1)
			{
				//orbisKeyboardInitWithConf(myConf->confKeyboard);
				ret=orbisKeyboardInit();
				debugNetPrintf(DEBUG,"orbisKeyboardInit %d\n",ret);
				if(ret==1)
				{
					myConf->confKeyboard=OrbisKeyboardGetConf();
					ret=orbisKeyboardOpen();
					debugNetPrintf(DEBUG,"orbisKeyboardOpen %d\n",ret);
				}
				//ret=orbisAudioInitChannel(ORBISAUDIO_CHANNEL_MAIN,512,48000,ORBISAUDIO_FORMAT_S16_MONO);
				//ret=orbisAudioInitChannel(ORBISAUDIO_CHANNEL_MAIN,1024,48000,ORBISAUDIO_FORMAT_S16_STEREO);
				//debugNetPrintf(DEBUG,"orbisKeyboardInit %d\n",orbisKeyboardInit());
				//sleep(1);
				//debugNetPrintf(DEBUG,"orbisKeyboardInit %d\n",orbisKeyboardOpen());
			
			}
		}
	}
	
}
int main(int argc, char *argv[])
{
	int ret;

	uintptr_t intptr=0;
	sscanf(argv[1],"%p",&intptr);
	myConf=(OrbisGlobalConf *)intptr;
	ret=ps4LinkInitWithConf(myConf->confLink);
	if(!ret)
	{
		ps4LinkFinish();
		return 0;
	}
	initApp();
	
	
	/*Mod_Init(0);
	Mod_Load("host0:zweifeld.mod");
	Mod_Play();*/
   // orbisAudioResume(0);
    orbisAudioPause(0);
	
	initTextures();
	debugNetPrintf(DEBUG,"after initTextures...\n");
	
	
	while(flag)
	{
		fmsxInit();
	}
	
	orbisAudioResume(0);
	//Mod_End();
	//wait for current display buffer
	orbis2dStartDrawing();

	// clear with background (default white) to the current display buffer 
	orbis2dClearBuffer(0);
					
	//flush and flip
	orbis2dFinishDrawing(flipArg);
			
	//swap buffers
	orbis2dSwapBuffers();
	
	finishApp();

	exit(0);

	return 0;
}
