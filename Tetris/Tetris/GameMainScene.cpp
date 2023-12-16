#include "GameMainScene.h"
#include "DxLib.h"
#include "Block.h"
#include "SceneManager.h"

/**********************************
*�}�N����`
**********************************/

/**********************************
*�^��`
**********************************/

/**********************************
*�O���[�o���ϐ��錾
**********************************/
int BackGround_image;			//�w�i�摜�C���[�W
int BackGround_sound;			//BGM
int GameOver_sound;				//�Q�[���I�[�o�[SE
int Score;						//�X�R�A
int Level;						//���x��

/**********************************
*�v���g�^�C�v�錾
**********************************/

/**********************************
*�Q�[�����C�����:����������
* ���@��:�Ȃ�
* �߂�l:�G���[���
**********************************/
int GameMainScene_Initialize(void)
{
	int ret = 0;

	ret = Block_Initialize();
	BackGround_image = LoadGraph("images/stage.png");
	BackGround_sound = LoadSoundMem("sounds/BGM017.ogg");
	GameOver_sound = LoadSoundMem("sounds/GameOver.mp3");
	Score = 0;

	//�G���[�`�F�b�N
	if (BackGround_image == -1)
	{
		ret = -1;
	}
	if (BackGround_sound == -1)
	{
		ret = -1;
	}
	return ret;
}

/**********************************
*�Q�[�����C�����:�X�V����
* ���@��:�Ȃ�
* �߂�l:�Ȃ�
**********************************/
void GameMainScene_Update(void)
{
	//BGM�̍Đ�
	PlaySoundMem(BackGround_sound, DX_PLAYTYPE_LOOP, FALSE);

	//�u���b�N�@�\�̍X�V
	Block_Update();
	int Line_Count;

	Line_Count = Get_Line();
	if (Get_Combo() <= 1)
	{
		if (Line_Count >= 4)
		{
			Score += Line_Count * 50 * 2;
		}
		else
		{
			Score += Line_Count * 50;
		}
	}
	else
	{
		if (Line_Count >= 4)
		{
			Score += Line_Count * 50 * 2 * Get_Combo();
		}
		else
		{
			Score += Line_Count * 50 * Get_Combo();
		}
	}


	if (Level < 5)
	{
		Level = Score / 500 + 1;
	}

	//�Đ��ł��Ȃ��Ȃ�����
	if (Get_GenerateFlg() != TRUE)
	{
		PlaySoundMem(GameOver_sound, DX_PLAYTYPE_BACK, FALSE);
		Change_Scene(E_RANKING);
		StopSoundMem(BackGround_sound);
	}
}

/**********************************
*�Q�[�����C�����:�`�揈��
* ���@��:�Ȃ�
* �߂�l:�Ȃ�
**********************************/
void GameMainScene_Draw(void)
{
	//�w�i�̕`��
	DrawGraph(0, 0, BackGround_image, TRUE);
	//�u���b�N�̕`��
	Block_Draw();
	SetFontSize(100);
	//�X�R�A��`��
	DrawFormatString(800, 100, GetColor(255, 255, 255), "%d", Score);
	DrawFormatString(800, 200, GetColor(255, 255, 255), "%d", Level);
	DrawFormatString(825, 300, GetColor(255, 255, 255), "%d", Get_Combo());
	SetFontSize(70);
	DrawFormatString(760, 400, 0xffffff, "COMBO");
	SetFontSize(20);
}

/**********************************
*�Q�[�����C�����:�X�R�A�擾����
* ���@��:�Ȃ�
* �߂�l:�Ȃ�
**********************************/
int Get_Score(void)
{
	return Score;
}

/**********************************
*�Q�[�����C�����:���x���擾����
* ���@��:�Ȃ�
* �߂�l:�Ȃ�
**********************************/
int Get_Level(void)
{
	return Level;
}