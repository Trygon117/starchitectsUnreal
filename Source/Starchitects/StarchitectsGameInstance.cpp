// Fill out your copyright notice in the Description page of Project Settings.
// Youtube Tutorial for Websockets: https://www.youtube.com/watch?v=l9TTmtDBTWY
// WebSockets Documentation: https://docs.unrealengine.com/4.27/en-US/API/Runtime/WebSockets/
// FJsonObject Documentaion: https://docs.unrealengine.com/4.27/en-US/API/Runtime/Json/Dom/FJsonObject/

#include "StarchitectsGameInstance.h"
#include "WebSocketsModule.h"
#include "Json.h"
#include "UObject/ConstructorHelpers.h"
#include "Misc/DateTime.h"
#include "Math/UnrealMathUtility.h"
#include "Math/Vector.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Serialization/JsonSerializer.h"

void UStarchitectsGameInstance::Init()
{
    Super::Init();

    if (!FModuleManager::Get().IsModuleLoaded("WebSockets"))
    {
        FModuleManager::Get().LoadModule("WebSockets");
    }

    const FString ServerURL = TEXT("wss://starchitects-a6e55037181c.herokuapp.com/"); // Your server URL. You can use ws, wss or wss+insecure.
    //const FString ServerURL = TEXT("ws://127.0.0.1:3000/"); // Your server URL. You can use ws, wss or wss+insecure.
    const FString ServerProtocol = TEXT("ws");              // The WebServer protocol you want to use.

    WebSocket = FWebSocketsModule::Get().CreateWebSocket(ServerURL, ServerProtocol);

    WebSocket->OnConnected().AddLambda([&]() {
        //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "Successfully Connected");
        UE_LOG(LogTemp, Warning, TEXT("Connecting..."));
        WebSocket->Send("{\"header\":0, \"data\":\"\"}");
    });

    WebSocket->OnConnectionError().AddLambda([](const FString& Error) {
        //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, Error);
    });

    WebSocket->OnClosed().AddLambda([](int32 StatusCode, const FString& Reason, bool bWasClean) {
        //GEngine->AddOnScreenDebugMessage(-1, 15.0f, bWasClean ? FColor::Green : FColor::Red, "Connection Closed: " + Reason);
    });

    WebSocket->OnMessage().AddLambda([&](const FString& Message) {
        //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, "Recieved Message: " + Message);
        UE_LOG(LogTemp, Warning, TEXT("Recieved Message: \"%s\"."), *Message);

        TSharedPtr<FJsonObject> JSON = UStarchitectsGameInstance::ParseJSON(Message);
        FString header = JSON->GetStringField("header");
        UE_LOG(LogTemp, Warning, TEXT("Recieved Header: \"%s\"."), *header);

        if (header == "0") {
            // error
            FString data = JSON->GetStringField("data");
            UE_LOG(LogTemp, Warning, TEXT("Error: \"%s\"."), *data);
        }
        else if (header == "1") {
            // all stars
            UStarchitectsGameInstance::LoadStars(JSON->GetArrayField("data"));
        }
        else if (header == "2") {
            // new star
            UStarchitectsGameInstance::AddStar(JSON->GetObjectField("data"));
        }
        else if (header == "3") {
            // sparkle animation
            UStarchitectsGameInstance::CallSparkleAnimation(JSON->GetStringField("data"));
        }
        else if (header == "4") {
            // twirl animation
            UStarchitectsGameInstance::CallTwirlAnimation(JSON->GetStringField("data"));
        }
        else if (header == "5") {
            // supernova animation
            UStarchitectsGameInstance::CallSupernovaAnimation(JSON->GetStringField("data"));
        }
        else {
            UE_LOG(LogTemp, Error, TEXT("No Header."));
        }
    });

    WebSocket->OnRawMessage().AddLambda([](const void* Data, SIZE_T Size, SIZE_T BytesRemaining) {
        // This code will run when we receive a raw (binary) message from the server.
        //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, "Recieved Raw Message");
        UE_LOG(LogTemp, Warning, TEXT("Recieved Raw Message"));
    });

    WebSocket->OnMessageSent().AddLambda([](const FString& Message) {
        //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Sent Message: " + Message);
    });

    // if (GEngine)
        // GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Hello!"));

    // example send message
    // WebSocket->Send("Test Message");

    WebSocket->Connect();

    // AddStarDebug();

    starBase = GetWorld()->SpawnActor<AStarBase>(AStarBase::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);

    // switch the currently tracked star every 10 seconds
    TimerManager->SetTimer(trackNewStarHandle, this, &UStarchitectsGameInstance::TrackNewStar, 10, true, 0);
    // move the camera to track the currently tracked star every 0.1 seconds
    TimerManager->SetTimer(trackStarHandle, this, &UStarchitectsGameInstance::TrackStar, 0.005, true, 0);
}

void UStarchitectsGameInstance::Shutdown()
{

    if (WebSocket->IsConnected())
    {
        WebSocket->Close();
    }

    Super::Shutdown();
}

void UStarchitectsGameInstance::LoadStars(TArray<TSharedPtr<FJsonValue>> starsJSON)
{
    //UE_LOG(LogTemp, Warning, TEXT("Loading Stars"));


    if (starsJSON.Num() != 0)
    {
        for (int i = 0; i < starsJSON.Num(); i++)
        {
            TSharedPtr<FJsonObject> obj = starsJSON[i]->AsObject();
            FStarData data;
            FString name = obj->GetStringField("name");
            data.name = name;
            data.color = (float)obj->GetNumberField("starColor");
            data.size = (float)obj->GetNumberField("size");
            data.shade = (float)obj->GetNumberField("starShade");
            data.shape = obj->GetIntegerField("shape");
            data.particleType = obj->GetIntegerField("dustType");
            data.particleColor = (float)obj->GetNumberField("dustColor");
            data.particleShade = (float)obj->GetNumberField("dustShade");
            FDateTime parsedBirthDate;
            FString birthDateString = obj->GetStringField("birthDate");
            bool converted = FDateTime::ParseIso8601(*birthDateString, parsedBirthDate);
            data.birthDate = parsedBirthDate;
            data.position = FVector::ZeroVector;
            //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "loaded star: " + name);
            CreateStar(data, obj->GetStringField("id"));
        }
    }


    //int32 length = starsJSON.Num();
    //FString name = starsJSON[0]->GetStringField("name");
    //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, starsJSON[0]->AsString());
    //UE_LOG(LogTemp, Warning, TEXT("Length: " + length.ToString()));
    // TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(json);

    // return if json is not parseable

    // for each json in the web socket
    // FStarData data
    // get each data from the array and add it to the map
}

void UStarchitectsGameInstance::AddStar(TSharedPtr<FJsonObject> starJSON)
{
    //UE_LOG(LogTemp, Warning, TEXT("Adding Star"));
    FStarData data;

    data.name = starJSON->GetStringField("name");
    data.shape = starJSON->GetIntegerField("shape");
    data.color = (float)starJSON->GetNumberField("starColor");
    //data.size = (float) starJSON->GetNumberField("size");
    data.shade = (float)starJSON->GetNumberField("starShade");
    data.shape = starJSON->GetIntegerField("shape");
    data.particleType = starJSON->GetIntegerField("dustType");
    data.particleColor = (float)starJSON->GetNumberField("dustColor");
    data.particleShade = (float)starJSON->GetNumberField("dustShade");
    FDateTime parsedBirthDate;
    FString birthDateString = starJSON->GetStringField("birthDate");
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "birthDateString: " + birthDateString);
    FDateTime::ParseIso8601(*birthDateString, parsedBirthDate);
    data.birthDate = parsedBirthDate;
    data.position = FVector::ZeroVector;
    CreateStar(data, starJSON->GetStringField("id"));
}

void UStarchitectsGameInstance::CreateStar(FStarData data, FString ID)
{
    //UE_LOG(LogTemp, Warning, TEXT("Adding Star"));
    FVector direction = FVector(FMath::RandRange(-100, 100), FMath::RandRange(-100, 100), FMath::RandRange(-30, 30));
    direction.Normalize();
    data.distance = FMath::Abs(FDateTime::Now().ToUnixTimestamp() - data.birthDate.ToUnixTimestamp());
    // UE_LOG(LogTemp, Log, TEXT("distance: " + data.distance));
    // GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::SanitizeFloat(data.distance));
    if (data.distance < 5000) {
        data.distance += 5000;
    }
    else if (data.distance > 50000) {
        data.distance = FMath::RandRange(50000, 100000);
    }
    data.position = direction * data.distance;
    AStarObj* newStar = GetWorld()->SpawnActor<AStarObj>(AStarObj::StaticClass(), data.position, FRotator::ZeroRotator);
    newStar->SetUpData(data);
    newStar->ID = ID;
    newStar->AttachToActor(starBase, FAttachmentTransformRules::KeepRelativeTransform);

    starClass.Add(newStar);
    // track this star for a full 30 seconds: 
    TimerManager->SetTimer(trackNewStarHandle, this, &UStarchitectsGameInstance::TrackNewStar, 10, true, 30);
    trackingIndex = starClass.Num() - 1;
}

void UStarchitectsGameInstance::TrackNewStar()
{
    UE_LOG(LogTemp, Warning, TEXT("Tracking New Star"));

    if (trackingIndex == -1) { // -1 means that there are no stars
        return;
    }

    int32 newIndex = trackingIndex + 1;
    bool foundStar = false;
    int32 checkedStars = 0;

    while (!foundStar) {
        if (newIndex >= starClass.Num()) { // loop back to the first star   
            newIndex = 0;
        }
        else if (starClass[newIndex]->distance > 75000) { // stars further than this wont be tracked
            if (checkedStars >= starClass.Num()) { // if every star has already failed to meet this criteria
                // just switch to the next star
                if (newIndex + 1 >= starClass.Num()) { // check if we need to loop back to 0
                    newIndex = 0;
                }
                else {
                    newIndex++;
                }
                foundStar = true;
            }
            else {
                newIndex++;
                checkedStars++;
            }
        }
        else {
            foundStar = true;
        }
    }

    trackingIndex = newIndex;
}

void UStarchitectsGameInstance::TrackStar()
{
    // UE_LOG(LogTemp, Warning, TEXT("Tracking Star"));
    if (trackingIndex == -1) {
        return;
    }
    AStarObj* trackingStar = starClass[trackingIndex];
    // Make the Camera Track this star if it is being tracked (if more than one is being tracked, it will track whichever one does this last)
    APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    FRotator currentRotation = playerController->GetControlRotation();
    FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(FVector::ZeroVector, trackingStar->GetActorLocation());

    playerController->RotationInput = targetRotation - currentRotation;
    // playerController->UpdateRotation(FDateTime::Now().ToUnixTimestamp() - trackingDelta);
    // trackingDelta = FDateTime::Now().ToUnixTimestamp();
}

void UStarchitectsGameInstance::AddStarDebug()
{

}

void UStarchitectsGameInstance::CallSparkleAnimation(FString starID)
{
    AStarObj* baseStar = NULL;
    int32 newIndex = -1;

    for (int i = 0; i < starClass.Num(); i++)
    {
        if (starClass[i]->ID == starID) {
            newIndex = i;
            baseStar = starClass[i];
        }
    }

    if (baseStar != NULL) {
        baseStar->SparkleAnimation();
        if (newIndex != -1) {
            TimerManager->SetTimer(trackNewStarHandle, this, &UStarchitectsGameInstance::TrackNewStar, 10, true, 5);
            trackingIndex = newIndex;
        }
    }
}

void UStarchitectsGameInstance::CallTwirlAnimation(FString starID)
{
    AStarObj* baseStar = NULL;
    int32 newIndex = -1;

    for (int i = 0; i < starClass.Num(); i++)
    {
        if (starClass[i]->ID == starID) {
            newIndex = i;
            baseStar = starClass[i];
        }
    }

    if (baseStar != NULL)
    {
        baseStar->TwirlAnimation();
        if (newIndex != -1) {
            TimerManager->SetTimer(trackNewStarHandle, this, &UStarchitectsGameInstance::TrackNewStar, 10, true, 5);
            trackingIndex = newIndex;
        }
    }
}

void UStarchitectsGameInstance::CallSupernovaAnimation(FString starID)
{
    AStarObj* baseStar = NULL;
    int32 newIndex = -1;

    for (int i = 0; i < starClass.Num(); i++)
    {
        if (starClass[i]->ID == starID) {
            newIndex = i;
            baseStar = starClass[i];
        }
    }

    if (baseStar != NULL) {
        baseStar->SupernovaAnimation();
        if (newIndex != -1) {
            TimerManager->SetTimer(trackNewStarHandle, this, &UStarchitectsGameInstance::TrackNewStar, 10, true, 5);
            trackingIndex = newIndex;
        }
    }
}

void UStarchitectsGameInstance::EndAnimations(FString starID)
{
    UE_LOG(LogTemp, Log, TEXT("Ending Animations"));
    WebSocket->Send("{\"header\":0, \"data\": \"" + starID + "\"}");
}

TSharedPtr<FJsonObject> UStarchitectsGameInstance::ParseJSON(FString json)
{
    TSharedPtr<FJsonObject> RetJsonObject;
    // Try to convert string to json object. Output goes to RetJsonObject
    if (!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(json), RetJsonObject))
    {
        return nullptr;
    }

    return RetJsonObject;
}