#include "sounddata_manager.h"

CSoundData::CSoundData(){
	char buf[256];
	char *s_name[] = {
		"bgm\\tit__popでかわいいダンス曲.mp3", "bgm\\nor__spoon.mp3","bgm\\bos__Aquilegia.mp3",
		"bgm\\go__げーむおーばー.mp3", "bgm\\gc__ファンファーレは誰のために？.mp3", 
		"se\\セレクト音_4.mp3", "se\\stn__se_maoudamashii_element_thunder04.mp3",
		"se\\magic-wind02.mp3","se\\bomb__Big_Hits.mp3", "se\\card-open1.mp3",
		"se\\highspeed-movement1.mp3","se\\コイン_2.mp3","se\\通常回復SE.mp3", "se\\edead__ポップな爆発.mp3",
		"se\\打撃・ビンタ音.mp3"
	};
	for (int i = 0; i < SOUND_NUM; i++){
		sprintf_s(buf, "media\\music\\%s", s_name[i]);
		sound[i] = LoadSoundMem(buf);
	}
	CSoundManager::GetInstance()->Init(this);
}

CSoundData::~CSoundData(){
	InitSoundMem();
}