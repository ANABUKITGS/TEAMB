#include "ui_manager.h"
#include "ui.h"

void CRightRotation::rotation(CUiData *cd){
	for (int i = 2; i > -1; i--){
		CUiData _a1;
		if (i != 0){
			_a1 = cd[i];
			cd[i] = cd[i - 1];
			cd[i - 1] = _a1;
		}
		else if (i == -1){
			_a1 = cd[i];
			cd[i] = cd[i + 3];
			cd[i + 3] = _a1;
		}
	}
}

void CLeftRotation::rotation(CUiData *cd){
	for (int i = 0; i < 3; i++){
		CUiData _a1;
		if (i != 2){
			_a1 = cd[i];
			cd[i] = cd[i + 1];
			cd[i + 1] = _a1;
		}
		else if (i == 3){
			_a1 = cd[i];
			cd[i] = cd[i - 2];
			cd[i - 2] = _a1;
		}
	}
}

void CRightIcon::IconDraw(CUiData *cd){
	for (int i = 0; i < 3; i++){
		DrawRotaGraph(cd[i].m_pos.getX(), cd[i].m_pos.getY(), cd[i].m_exrate, cd[i].m_rad, /*m_icon_img[cd[i].m_animtype][cd[i].m_amine_rate]*/
			CUiManager::GetInstance()->GetUiAdress()->GetImg(cd[i].m_animtype, cd[i].m_amine_rate),TRUE, FALSE);
	}
}

void CLeftIcon::IconDraw(CUiData *cd){
	for (int i = 2; i > -1; i--){
		DrawRotaGraph(cd[i].m_pos.getX(), cd[i].m_pos.getY(), cd[i].m_exrate, cd[i].m_rad,
			CUiManager::GetInstance()->GetUiAdress()->GetImg(cd[i].m_animtype, cd[i].m_amine_rate)/*m_icon_img[cd[i].m_animtype][cd[i].m_amine_rate]*/, TRUE, FALSE);
	}
}

void CTimer::Update(CUiData *cd){
	if (cd->m_timer < TIME_LIMIT)
		cd->m_timer++;
	cd->m_rad = cd->m_timer / TIME_SPLIT / TIME_CIRCLE_SPLIT;
}

void CSecondHand::Update(CUiData *cd){
	if (cd->m_timer < TIME_LIMIT)
		cd->m_timer++;
	else
		CUiManager::GetInstance()->GetUiAdress()->SetTimeFlag(true);
	cd->m_rad = cd->m_timer / TIME_SPLIT;
}

void CComb::Update(CUiData *cd){
	if (CUiManager::GetInstance()->GetUiAdress()->GatComb() > 0){
		if (cd->m_living == false){
			cd->m_living = true;
		}
		if (cd->m_exrate > 0.6f){
			cd->m_exrate -= 0.03;
		}
		if (cd->m_alpha < 256){
			cd->m_alpha += 25;
		}
	}
	else{
		if (cd->m_exrate < 1.1f){
			cd->m_exrate += 0.01f;
			cd->m_alpha -= 23;
		}
		else{
			cd->m_living = false;
			
		}
	}
}

void CItemText::Update(CUiData *cd){
	if (cd->m_pos.getX() >  430 + cd->m_mass){
		cd->m_pos.addX(-7);
		if (cd->m_alpha < 256)
			cd->m_alpha += 10;
		else
			cd->m_alpha = 255;
	}
	else if (cd->m_pos.getX() > 370 + cd->m_mass){
		cd->m_pos.addX(-1);
	}
	else{
		cd->m_pos.addX(-7);
		if (cd->m_alpha > 0)
			cd->m_alpha -= 10;
		else
			cd->m_living = false;

	}
}