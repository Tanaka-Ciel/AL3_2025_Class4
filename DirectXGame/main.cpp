#include <Windows.h>
#include <KamataEngine.h>
#include "Gamescene.h"
using namespace KamataEngine;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int){

	//エンジンの初期化
	KamataEngine::Initialize(L"LE2D_14_タナカ_シエル_AL3");

	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	//ゲームシーンのインスタンス生成
	Gamescene* gamescene = new Gamescene();
	//ゲームシーンの初期化
	gamescene->Initialize();

	//メインループ
	while (true) {
		//エンジンの更新
		if (KamataEngine::Update()) {
			break;
		}

		//ゲームシーンの更新
		gamescene->Update();

		//描画開始
		dxCommon->PreDraw();

		//ゲームシーンの描画
		gamescene->Draw();


		//描画終了
		dxCommon->PostDraw();
	}

	//ゲームシーンの解放
	delete gamescene;
	//nullptrの代入
	gamescene = nullptr;


	//エンジンの終了処理
	KamataEngine::Finalize();

	return 0;
}
