#include "Gamescene.h"
#include "Mymath.h"

using namespace KamataEngine;

// デストラクタ
Gamescene::~Gamescene() { 
	delete sprite_;
	delete model_;
	delete player_;
	delete debugCamera_;
	delete modelSkydome_;
	delete mapChipField_;

	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			delete worldTransformBlock;
		}
	}
	worldTransformBlocks_.clear();
}

void Gamescene::Initialize() { 
	//ファイル名を指定してテクスチャを読み込む
	//textureHandle_ = TextureManager::Load("debugfont.png"); 

	sprite_ = Sprite::Create(textureHandle_, {100, 50});

	//3Dモデルの生成
	model_ = Model::CreateFromOBJ("block", true);

	//カメラの初期化
	camera_.Initialize();

	//自キャラの生成
	player_ = new Player();

	modelplayer_ = Model::CreateFromOBJ("player", true);

	//自キャラの初期化
	player_->Initialize(modelplayer_, textureHandle_, &camera_);


	modelSkydome_ = Model::CreateFromOBJ("skydome", true);

	skydome_ = new Skydome();

	skydome_->Initialize(modelSkydome_, textureHandle_, &camera_);

	mapChipField_ = new MapChipField;
	mapChipField_->LoadMapChipCsv("Resources/blocks.csv");

	GenerateBlocks();

	//デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);
}

void Gamescene::Update() {
	#ifdef _DEBUG
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)){
		isDebugCameraActive_=!isDebugCameraActive_;
	}
	#endif

	Vector2 position = sprite_->GetPosition();

	if (isDebugCameraActive_) 
	{
		// デバッグカメラの更新
		debugCamera_->Update();
		// デバッグカメラのビュー行列
		camera_.matView = camera_.matView = debugCamera_->GetCamera().matView;
		// デバッグカメラのプロジェクション行列
		camera_.matProjection = camera_.matProjection = debugCamera_->GetCamera().matProjection;
		//ビュープロジェクション行列の転送
		camera_.TransferMatrix();
	} else {
		//ビュープロジェクション行列の更新と転送
		camera_.UpdateMatrix();
	}

	position.x += 2.0f;
	position.y += 1.0f;

	sprite_->SetPosition(position);
	player_->Update();

	//ブロックの更新
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock)
				continue;
			worldTransformBlock->matWorld_ = MakeAffineMatrix(worldTransformBlock->scale_, worldTransformBlock->rotation_, worldTransformBlock->translation_);
			worldTransformBlock->TransferMatrix();
		}
	}
}

void Gamescene::Draw() {

	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	Sprite::PreDraw(dxCommon->GetCommandList());

	sprite_->Draw();

	Sprite::PostDraw();



	Model::PreDraw(dxCommon->GetCommandList());

	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock)
				continue;
			model_->Draw(*worldTransformBlock, camera_);
		}
	}

	player_->Draw();

	skydome_->Draw();

	Model::PostDraw();

	
}

void Gamescene::GenerateBlocks() { 
	uint32_t numBlockVirtical = mapChipField_->GetNumBlockVirtical(); 
	uint32_t numBlockHorizontal = mapChipField_->GetNumBlockHorizontal();

	worldTransformBlocks_.resize(numBlockVirtical);
	for (uint32_t i = 0; i < numBlockVirtical; ++i) 
	{
		worldTransformBlocks_[i].resize(numBlockHorizontal);
		for (uint32_t j = 0; j < numBlockHorizontal; ++j)
		{
			if (mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kBlock) 
			{
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransformBlocks_[i][j] = worldTransform;
				worldTransformBlocks_[i][j]->translation_ = mapChipField_->GetMapChipPositionByIndex(j, i);
			}
		}
	}
}
