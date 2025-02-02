#include "MainMenuScene.h"
#include <iostream>

void MainMenuScene::InitializeButtons()
{
    int screenWidth = mFrame->GetWidth();
    int screenHeight = mFrame->GetHeight();
    int centerX = screenWidth / 2;
    int centerY = screenHeight / 2;

    // 멀티 모드 버튼 설정
    mMultiMode.SetPosition(14, centerY - 3);
    mMultiMode.resize(6, 3); // 예: 가로 40, 세로 3
    mMultiMode.setOnClick([this]() {
        mSceneManager->RequestSceneChange(SceneType::Playing);
    });

    // 싱글 모드 버튼 설정
    mSingleMode.SetPosition(14, centerY + 3);
    mSingleMode.resize(6, 3);
    mSingleMode.setOnClick([this]() {
        mSceneManager->RequestSceneChange(SceneType::Playing);
    });
}

MainMenuScene::MainMenuScene(ConsoleRenderer & renderer, InputManager * inputManager, SceneManager* sceneManager)
    : Scene(renderer, inputManager, sceneManager) {
    
     mRenderer.Clear();
     mFrame = mRenderer.AddFrame(0, 0, 40, 30);
	 mFrame->Clear();
     mSingleMode = Button{inputManager, mFrame};
     mMultiMode = Button{inputManager, mFrame};
     InitializeButtons();
     mFrame->SetText(5, 5, L"Welcome to Tetris!", static_cast<WORD>(ConsoleColor::BrightGreen));
     mFrame->SetText(5, 6, L"Press Enter to Start", static_cast<WORD>(ConsoleColor::BrightWhite));
}

void MainMenuScene::Update() {
    // Enter 키 입력 시 상태 전환
    int key = mInputManager->DequeueInput();
    int button = mInputManager->DequeueMouseInput();

    auto mousePos = mInputManager->GetMousePosition();
    int mouseX = mousePos.x;
    int mouseY = mousePos.y;

    if (key == VK_RETURN || button == MOUSE_LEFT) {
        mSceneManager->RequestSceneChange(SceneType::Playing);
    }
 
    if (button == MOUSE_LEFT && mSingleMode.contains(mouseX, mouseY))
        mSingleMode.click();
    if (button == MOUSE_LEFT && mMultiMode.contains(mouseX, mouseY))
        mMultiMode.click();

}

void MainMenuScene::Draw() {
    // 메인 메뉴 화면 텍스트
    mSingleMode.draw();
    mSingleMode.setText(L"Single");
    mMultiMode.draw();
    mMultiMode.setText(L"Multi");
    mRenderer.Render();
}

   