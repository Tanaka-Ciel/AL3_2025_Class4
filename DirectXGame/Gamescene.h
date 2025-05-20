#pragma once
#include "KamataEngine.h"
#include "Player.h"
#include <vector>



//ゲームシーン
class Gamescene 
{
public:

	KamataEngine::WorldTransform worldTransform;
	KamataEngine::Sprite* sprite_ = nullptr;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Camera camera_;
	Player* player_ = nullptr;
	std::vector<std::vector<KamataEngine::WorldTransform*>> worldTransformBlocks_;

		//初期化
	    void Initialize();

		//更新
	    void Update();

		//描画
	    void Draw();

		~Gamescene();

		//デバッグカメラ有効
	    bool isDebugCameraActive_ = false;

		//デバッグカメラ
	    KamataEngine::DebugCamera* debugCamera_ = nullptr;


private:

		uint32_t textureHandle_ = 0;

};
