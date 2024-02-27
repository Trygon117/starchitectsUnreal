// Fill out your copyright notice in the Description page of Project Settings.
// Youtube Tutorial for Websockets: https://www.youtube.com/watch?v=l9TTmtDBTWY
// WebSockets Documentation: https://docs.unrealengine.com/4.27/en-US/API/Runtime/WebSockets/


#include "StarchitectsGameInstance.h"
#include "WebSocketsModule.h"
#include "UObject/ConstructorHelpers.h"

void UStarchitectsGameInstance::Init() {
    Super::Init();

    if(!FModuleManager::Get().IsModuleLoaded("WebSockets")) {
        FModuleManager::Get().LoadModule("WebSockets");
    }

    WebSocket = FWebSocketsModule::Get().CreateWebSocket("ws://127.0.0.1:443");

    WebSocket->OnConnected().AddLambda([&]() {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "Successfully Connected");
        WebSocket->Send("0");
    });

    WebSocket->OnConnectionError().AddLambda([](const FString& Error) {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, Error);
    });

    WebSocket->OnClosed().AddLambda([](int32 StatusCode, const FString& Reason, bool bWasClean) {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, bWasClean ? FColor::Green : FColor::Red, "Connection Closed: " + Reason);
    });

    WebSocket->OnMessage().AddLambda([](const FString& Message) {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, "Recieved Message: " + Message);
    });

    WebSocket->OnMessageSent().AddLambda([](const FString& Message) {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Sent Message: " + Message);
    });

    if(GEngine)
     GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Hello!"));

    // example send message
    // WebSocket->Send("Test Message");

    WebSocket->Connect();

    //AddStarDebug();

    AStarObj* newStar = GetWorld()->SpawnActor<AStarObj>(AStarObj::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
    newStar->SetActorRelativeScale3D(FVector::OneVector);
}

void UStarchitectsGameInstance::Shutdown() {

    if(WebSocket->IsConnected()) {
        WebSocket->Close();
    }

    Super::Shutdown();
}

void UStarchitectsGameInstance::LoadStars(FString json){

    TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(json);

    //return if json is not parseable

    //for each json in the web socket
    //FStarData data 
    //get each data from the array and add it to the map
}

void UStarchitectsGameInstance::AddStar(){

}

void UStarchitectsGameInstance::AddStarDebug(){
    //static ConstructorHelpers::FClassFinder<AActor> StarClassFinder(TEXT("/Game/Star"));
    //bool doesItExit = StarClassFinder.Class == NULL;
    //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, doesItExit ? "False" : "True");

    //StarClass = StarClassFinder.Class;

    //AActor* newStar = GetWorld()->SpawnActor<AActor>(StarClass, FVector::ZeroVector, FRotator::ZeroRotator);

    AStarObj* newStar = GetWorld()->SpawnActor<AStarObj>(AStarObj::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator); 
}