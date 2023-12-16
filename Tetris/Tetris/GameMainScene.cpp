#include "GameMainScene.h"
#include "DxLib.h"
#include "Block.h"
#include "SceneManager.h"

/**********************************
*マクロ定義
**********************************/

/**********************************
*型定義
**********************************/

/**********************************
*グローバル変数宣言
**********************************/
int BackGround_image;			//背景画像イメージ
int BackGround_sound;			//BGM
int GameOver_sound;				//ゲームオーバーSE
int Score;						//スコア
int Level;						//レベル

/**********************************
*プロトタイプ宣言
**********************************/

/**********************************
*ゲームメイン画面:初期化処理
* 引　数:なし
* 戻り値:エラー情報
**********************************/
int GameMainScene_Initialize(void)
{
	int ret = 0;

	ret = Block_Initialize();
	BackGround_image = LoadGraph("images/stage.png");
	BackGround_sound = LoadSoundMem("sounds/BGM017.ogg");
	GameOver_sound = LoadSoundMem("sounds/GameOver.mp3");
	Score = 0;

	//エラーチェック
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
*ゲームメイン画面:更新処理
* 引　数:なし
* 戻り値:なし
**********************************/
void GameMainScene_Update(void)
{
	//BGMの再生
	PlaySoundMem(BackGround_sound, DX_PLAYTYPE_LOOP, FALSE);

	//ブロック機能の更新
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

	//再生できなくなったら
	if (Get_GenerateFlg() != TRUE)
	{
		PlaySoundMem(GameOver_sound, DX_PLAYTYPE_BACK, FALSE);
		Change_Scene(E_RANKING);
		StopSoundMem(BackGround_sound);
	}
}

/**********************************
*ゲームメイン画面:描画処理
* 引　数:なし
* 戻り値:なし
**********************************/
void GameMainScene_Draw(void)
{
	//背景の描画
	DrawGraph(0, 0, BackGround_image, TRUE);
	//ブロックの描画
	Block_Draw();
	SetFontSize(100);
	//スコアを描画
	DrawFormatString(800, 100, GetColor(255, 255, 255), "%d", Score);
	DrawFormatString(800, 200, GetColor(255, 255, 255), "%d", Level);
	DrawFormatString(825, 300, GetColor(255, 255, 255), "%d", Get_Combo());
	SetFontSize(70);
	DrawFormatString(760, 400, 0xffffff, "COMBO");
	SetFontSize(20);
}

/**********************************
*ゲームメイン画面:スコア取得処理
* 引　数:なし
* 戻り値:なし
**********************************/
int Get_Score(void)
{
	return Score;
}

/**********************************
*ゲームメイン画面:レベル取得処理
* 引　数:なし
* 戻り値:なし
**********************************/
int Get_Level(void)
{
	return Level;
}