#include <Novice.h>
#include <imgui.h>
#include <KamataEngine.h>
#include "MassFunction.h"
#include "DrawFunction.h"

const char kWindowTitle[] = "学籍番号";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};
	Vector3 rotate = { 0.0f, 0.0f, 0.0f };
	Vector3 traslate = { 0.0f, 0.0f, 0.0f };
	Vector3 cameraTranslate = { 0.0f, 1.9f, -6.49f };
	Vector3 cameraRotate = { 0.26f, 0.0f, 0.0f };

	Sphere sphereA = { { 0.0f, 0.0f, 0.0f }, 1.0f };
	Sphere sphereB = { { 5.0f, 0.0f, 5.0f }, 0.5f };
	unsigned int sphereColor = 0xFFFFFFFF; // 白色

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		
		// キー入力によるカメラの移動
		if (keys[DIK_W] != 0) cameraTranslate.z += 0.1f; // 前進
		if (keys[DIK_S] != 0) cameraTranslate.z -= 0.1f; // 後退	
		if (keys[DIK_A] != 0) cameraTranslate.x -= 0.1f; // 左移動
		if (keys[DIK_D] != 0) cameraTranslate.x += 0.1f; // 右移動




		bool ishit= IsCollision(sphereA, sphereB);
		if (ishit)
		{
			sphereColor = 0xFF0000FF; // 赤色
		} else
		{
			sphereColor = 0xFFFFFFFF; // 白色
		}


			ImGui::Begin("Window");
		ImGui::DragFloat3("SphierCenterA", &sphereA.center.x, 0.01f);
		ImGui::DragFloat("SphierRadiusA", &sphereA.radius, 0.01f);
		ImGui::DragFloat3("SphierCenterB", &sphereB.center.x, 0.01f);
		ImGui::DragFloat("SphierRadiusB", &sphereB.radius, 0.01f);
		ImGui::End();
		 
		Matrix4x4 worldMatrix = MakeAfineMatrix({ 1.0f, 1.0f, 1.0f }, rotate, traslate);
		//MatrixScreenPrintf(0, kRowHeight, worldMatrix, "worldMatrix");
		Matrix4x4 cameraMatrix = MakeAfineMatrix({ 1.0f, 1.0f, 1.0f },cameraRotate,cameraTranslate );
		//MatrixScreenPrintf(0, kRowHeight * 20, cameraMatrix, "cameraMatrix");
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		//MatrixScreenPrintf(0, kRowHeight * 30, viewMatrix, "viewMatrix");
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, static_cast<float>(kwindowWidth)/static_cast <float>(kwindowHight) , 0.1f, 100.0f);
		//MatrixScreenPrintf(kColumnWidth*10, kRowHeight  , projectionMatrix, "projectionMatrix");
		Matrix4x4 worldViewProjectionMatrix = Multiply( worldMatrix,Multiply(viewMatrix,projectionMatrix));
		//MatrixScreenPrintf(kColumnWidth*10, kRowHeight * 20, worldViewProjectionMatrix, "worldViewProjectionMatrix");
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0.0f, 0.0f, static_cast<float>(kwindowWidth), static_cast<float>(kwindowHight), 0.0f, 1.0f);
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		DrawGrid(worldViewProjectionMatrix,viewportMatrix);
		DrawSphere(sphereA, worldViewProjectionMatrix, viewportMatrix,sphereColor);
		DrawSphere(sphereB, worldViewProjectionMatrix, viewportMatrix,0xAAAAAAFF);
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
