-- 프로젝트 이름이 인자로 전달되었는지 확인합니다.
if _ARGS[1] then
    game_project = _ARGS[1]
    print(string.format("Setting '%s' visual studio solution name...", game_project))
else
    print("Missing visual studio solution name...")
    os.exit()
end

-- 프로젝트 루트 디렉토리입니다.
root_directory = _MAIN_SCRIPT_DIR

-- 게임 엔진 디렉토리입니다.
engine_directory = "%{root_directory}/GameEngine"

-- 서드 파티 라이브러리 디렉토리입니다.
thirdparty_directory = "%{engine_directory}/ThirdParty"

-- 게임 프로젝트 디렉토리입니다.
game_directory = "%{root_directory}/%{game_project}"

-- 게임 개발 작업 영역입니다.
workspace "%{game_project}"
    -- 빌드 구성 요소입니다.
    configurations {
        "Debug", 
        "Release", 
        "Shipping" 
    }

    -- 플랫폼을 설정합니다.
    platforms { "Win64" }

    -- 솔루션 경로를 설정합니다.
    location "%{root_directory}/Solution"

    -- 시작 프로젝트를 설정합니다.
    startproject "%{game_project}"

    -- 게임 엔진 프로젝트 설정을 추가합니다.
    include "GameEngine/project_config.lua"
    
    -- 시작 프로젝트 설정을 추가합니다.
    include "TappyPlane2D/project_config.lua"