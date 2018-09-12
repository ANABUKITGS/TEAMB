#include "sounddata_manager.h"

CSoundData::CSoundData(){
	char buf[256];
	char *s_name[] = {
		"bgm\\tit__pop�ł��킢���_���X��.mp3", "bgm\\2027.mp3", "bgm\\bos__Aquilegia.mp3",
		"bgm\\go__���[�ނ��[�΁[.mp3", "bgm\\gc__�t�@���t�@�[���͒N�̂��߂ɁH.mp3",
		"se\\�Z���N�g��_4.mp3", "se\\stn__se_maoudamashii_element_thunder04.mp3",
		"se\\magic-wind02.mp3", "se\\bomb__Big_Hits.mp3", "se\\card-open1.mp3",
		"se\\highspeed-movement1.mp3", "se\\�R�C��_2.mp3", "se\\�ʏ��SE.mp3", "se\\edead__�|�b�v�Ȕ���.mp3",
		"se\\�Ō��E�r���^��.mp3",
		"se\\se_item_drop.mp3", "se\\se_e_drop.mp3", "se\\se_e_normal.mp3", "se\\se_p_teleport.mp3", "se\\se_e_small.mp3",
		"se\\se_e_bullet.mp3", "se\\se_e_range.mp3", "se\\se_e_big.mp3", "se\\se_boss_attack.mp3",
		"se\\se_e_bomb.mp3", "se\\title_select.mp3", "se\\se_title_select.mp3",
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