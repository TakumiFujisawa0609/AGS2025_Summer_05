#include "ResourceManager.h"
#include <DxLib.h>
#include "../../Application.h"
#include "Resource.h"

ResourceManager* ResourceManager::instance_ = nullptr;

void ResourceManager::CreateInstance(void)
{
    if (instance_ == nullptr)
    {
        instance_ = new ResourceManager();
    }
    instance_->Init();
}

ResourceManager& ResourceManager::GetInstance(void)
{
    return *instance_;
}

void ResourceManager::Init(void)
{
}

void ResourceManager::InitTitle(void)
{
    Resource resource;

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "UI/sousa.png"
    );
    resourcesMap_.emplace(SRC::OPERATION, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "UI/mokuhyou.png"
    );
    resourcesMap_.emplace(SRC::PLAY_GUIDE, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "UI/renkint.png"
    );
    resourcesMap_.emplace(SRC::PLAY_GUIDE2, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "UI/titleRog.png"
    );
    resourcesMap_.emplace(SRC::TITLE_LOGO, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "UI/atrieT.png"
    );
    resourcesMap_.emplace(SRC::ATELIER, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "UI/girudo.png"
    );
    resourcesMap_.emplace(SRC::GUILD, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "UI/gadenT.png"
    );
    resourcesMap_.emplace(SRC::GARDEN, resource);

    resource = Resource(
        Resource::TYPE::SOUND,
        Application::PATH_BGM + "nc49298.mp3"
    );
    resourcesMap_.emplace(SRC::BGM_TITLE, resource);

    resource = Resource(
        Resource::TYPE::SOUND,
        Application::PATH_SE + "se_pikon19.mp3"
    );
    resourcesMap_.emplace(SRC::SE_PUSH, resource);

    resource = Resource(
        Resource::TYPE::SOUND,
        Application::PATH_SE + "nc298207.mp3"
    );
    resourcesMap_.emplace(SRC::SE_CANCEL, resource);

    resource = Resource(
        Resource::TYPE::SOUND,
        Application::PATH_SE + "Cursormovementsound.mp3"
    );
    resourcesMap_.emplace(SRC::SE_SELECT, resource);
}

void ResourceManager::InitGame(void)
{
    Resource resource;

    resource = Resource(
        Resource::TYPE::SOUND,
        Application::PATH_BGM + ""
    );
    resourcesMap_.emplace(SRC::BGM_GAME, resource);

    resource = Resource(
        Resource::TYPE::SOUND,
        Application::PATH_SE + "Cursormovementsound.mp3"
    );
    resourcesMap_.emplace(SRC::SE_SELECT, resource);

    resource = Resource(
        Resource::TYPE::SOUND,
        Application::PATH_SE + "se_pikon1.mp3"
    );
    resourcesMap_.emplace(SRC::SE_PUSH, resource);

    resource = Resource(
        Resource::TYPE::SOUND,
        Application::PATH_SE + "nc298207.mp3"
    );
    resourcesMap_.emplace(SRC::SE_CANCEL, resource);

    resource = Resource(
        Resource::TYPE::SOUND,
        Application::PATH_SE + ""
    );
    resourcesMap_.emplace(SRC::SE_DAMAGE, resource);

    resource = Resource(
        Resource::TYPE::SOUND,
        Application::PATH_SE + ""
    );
    resourcesMap_.emplace(SRC::SE_GET, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "UI/DHUI.png"
    );
    resourcesMap_.emplace(SRC::UI_FRAME, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "UI/moningUI.png"
    );
    resourcesMap_.emplace(SRC::MORNING, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "UI/HirumaUI.png"
    );
    resourcesMap_.emplace(SRC::DAY, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "UI/HiruUI.png"
    );
    resourcesMap_.emplace(SRC::EVENING, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "UI/nightUI.png"
    );
    resourcesMap_.emplace(SRC::NIGHT, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "UI/Maney.png"
    );
    resourcesMap_.emplace(SRC::MONEY, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "UI/Bloodinaleatherbag.png"
    );
    resourcesMap_.emplace(SRC::BLOOD_BAG, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "UI/cinnabar.png"
    );
    resourcesMap_.emplace(SRC::CINNABAR, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "UI/PhilosophersStone.png"
    );
    resourcesMap_.emplace(SRC::PHILOSOPHERS_STONE, resource);

    ResourcePlayer();
    ResourceEnemy();
    ResourceAtelier();
    ResourceGuild();
    ResourceGarden();
}

void ResourceManager::InitGameOver(void)
{
    Resource resource;

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + ""
    );
    resourcesMap_.emplace(SRC::GAMEOVER_LOGO, resource);

    resource = Resource(
        Resource::TYPE::SOUND,
        Application::PATH_BGM + ""
    );
    resourcesMap_.emplace(SRC::BGM_GAMEOVER, resource);

    resource = Resource(
        Resource::TYPE::SOUND,
        Application::PATH_SE + ""
    );
    resourcesMap_.emplace(SRC::SE_PUSH, resource);
}

void ResourceManager::InitGameClear(void)
{
    Resource resource;

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + ""
    );
    resourcesMap_.emplace(SRC::GAMECLEAR_LOGO, resource);

    resource = Resource(
        Resource::TYPE::SOUND,
        Application::PATH_BGM + ""
    );
    resourcesMap_.emplace(SRC::BGM_GAMECLEAR, resource);

    resource = Resource(
        Resource::TYPE::SOUND,
        Application::PATH_SE + ""
    );
    resourcesMap_.emplace(SRC::SE_PUSH, resource);
}

void ResourceManager::ResourceAtelier(void)
{
    Resource resource;

    resource = Resource(
        Resource::TYPE::MODEL,
        Application::PATH_MODEL + "/Atelier/hondana.mv1"
    );
    resourcesMap_.emplace(SRC::BOOK_SHELF, resource);

    resource = Resource(
        Resource::TYPE::MODEL,
        Application::PATH_MODEL + "/Atelier/renkingama.mv1"
    );
    resourcesMap_.emplace(SRC::ALCHEMYPOT, resource);

    resource = Resource(
        Resource::TYPE::MODEL,
        Application::PATH_MODEL + "/Atelier/AtelierStage.mv1"
    );
    resourcesMap_.emplace(SRC::STAGE_ATELIER, resource);

    resource = Resource(
        Resource::TYPE::MODEL,
        Application::PATH_MODEL + "/Atelier/Box.mv1"
    );
    resourcesMap_.emplace(SRC::BOX, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "item/Greenherb.png"
    );
    resourcesMap_.emplace(SRC::HERB, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "item/Purpleherb.png"
    );
    resourcesMap_.emplace(SRC::ANTIDOTE_HERB, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "item/BlueHerb.png"
    );
    resourcesMap_.emplace(SRC::MAGIC_FLOWER, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "item/Yellowherb.png"
    );
    resourcesMap_.emplace(SRC::PARALYSIS_HERB, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "item/Lightblueherb.png"
    );
    resourcesMap_.emplace(SRC::GALE_HERB, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "item/Redherb.png"
    );
    resourcesMap_.emplace(SRC::DEMON_POWER_HERB, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "item/Orangeherb.png"
    );
    resourcesMap_.emplace(SRC::HARD_BODY_HERB, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "item/GreenTriangularPotion.png"
    );
    resourcesMap_.emplace(SRC::RECOVERY_POTION, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "item/PurpleTriangularPotion.png"
    );
    resourcesMap_.emplace(SRC::ANTIDOTE_POTION, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "item/YellowPotion.png"
    );
    resourcesMap_.emplace(SRC::ANTIPARALYSIS_POTION, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "item/BlueTriangularPotion.png"
    );
    resourcesMap_.emplace(SRC::MAGIC_POTION, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "item/LightbluePotion.png"
    );
    resourcesMap_.emplace(SRC::SPEED_POTION, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "item/RedTriangularPotion.png"
    );
    resourcesMap_.emplace(SRC::POWER_POTION, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "item/OrangePotion.png"
    );
    resourcesMap_.emplace(SRC::DEFENSE_POTION, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "item/Water.png"
    );
    resourcesMap_.emplace(SRC::WATER, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "item/Iron.png"
    );
    resourcesMap_.emplace(SRC::IRON_ORE, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "item/RedOre.png"
    );
    resourcesMap_.emplace(SRC::FIRE_MAGIC_STONE, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "item/BlueOre.png"
    );
    resourcesMap_.emplace(SRC::WATER_MAGIC_STONE, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "item/GreenOre.png"
    );
    resourcesMap_.emplace(SRC::WIND_MAGIC_STONE, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "item/OrangeOre.png"
    );
    resourcesMap_.emplace(SRC::EARTH_MAGIC_STONE, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "item/WaterOre.png"
    );
    resourcesMap_.emplace(SRC::ICE_MAGIC_STONE, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "item/YellowOre.png"
    );
    resourcesMap_.emplace(SRC::LIGHT_MAGIC_STONE, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "item/PurpleOre.png"
    );
    resourcesMap_.emplace(SRC::DARK_MAGIC_STONE, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "item/Sword.png"
    );
    resourcesMap_.emplace(SRC::SWORD, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "item/RedSword.png"
    );
    resourcesMap_.emplace(SRC::FIRE_SWORD, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "item/BlueSword.png"
    );
    resourcesMap_.emplace(SRC::WATER_SWORD, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "item/GreenSword.png"
    );
    resourcesMap_.emplace(SRC::WIND_SWORD, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "item/OrangeSword.png"
    );
    resourcesMap_.emplace(SRC::EARTH_SWORD, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "item/WaterSword.png"
    );
    resourcesMap_.emplace(SRC::ICE_SWORD, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "item/YellowSword.png"
    );
    resourcesMap_.emplace(SRC::LIGHT_SWORD, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "item/PurpleSword.png"
    );
    resourcesMap_.emplace(SRC::DARK_SWORD, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "item/Cane.png"
    );
    resourcesMap_.emplace(SRC::WAND, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "item/RedWand.png"
    );
    resourcesMap_.emplace(SRC::FIRE_WAND, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "item/BlueWand.png"
    );
    resourcesMap_.emplace(SRC::WATER_WAND, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "item/GreenWand.png"
    );
    resourcesMap_.emplace(SRC::WIND_WAND, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "item/OrangeWand.png"
    );
    resourcesMap_.emplace(SRC::EARTH_WAND, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "item/WaterWand.png"
    );
    resourcesMap_.emplace(SRC::ICE_WAND, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "item/YellowWand.png"
    );
    resourcesMap_.emplace(SRC::LIGHT_WAND, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "item/PurpleWand.png"
    );
    resourcesMap_.emplace(SRC::DARK_WAND, resource);

    resource = Resource(
        Resource::TYPE::SOUND,
        Application::PATH_SE + "renkin.mp3"
    );
    resourcesMap_.emplace(SRC::SE_ALCHEMY, resource);

    resource = Resource(
        Resource::TYPE::SOUND,
        Application::PATH_SE + "nc46976.mp3"
    );
    resourcesMap_.emplace(SRC::SE_ALCHEMY_FAIL, resource);

    resource = Resource(
        Resource::TYPE::SOUND,
        Application::PATH_SE + "fanfare3.mp3"
    );
    resourcesMap_.emplace(SRC::SE_ALCHEMY_SUCCESS, resource);

    resource = Resource(
        Resource::TYPE::SOUND,
        Application::PATH_BGM + "m2.mp3"
    );
    resourcesMap_.emplace(SRC::BGM_ATELIER, resource);

    resource = Resource(
        Resource::TYPE::EFFEKSEER,
        Application::PATH_EFFECT + "Simple_Sprite_FixedYAxis.efkefc"
    );
    resourcesMap_.emplace(SRC::EFFECT_ALCHEMY, resource);

    resource = Resource(
        Resource::TYPE::EFFEKSEER,
        Application::PATH_EFFECT + "BlastHit.efkefc"
    );
    resourcesMap_.emplace(SRC::EFFECT_BLAST, resource);
}

void ResourceManager::ResourceGuild(void)
{
    Resource resource;

    resource = Resource(
        Resource::TYPE::MODEL,
        Application::PATH_MODEL + "/GuildObject/BulletinBoard.mv1"
    );
    resourcesMap_.emplace(SRC::BULLETIN_BOARD, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "/GuildStage/BulletinBoard.png"
    );
    resourcesMap_.emplace(SRC::IMAGE_BOARD, resource);

    resource = Resource(
        Resource::TYPE::MODEL,
        Application::PATH_MODEL + "/GuildObject/counter.mv1"
    );
    resourcesMap_.emplace(SRC::COUNTER, resource);

    resource = Resource(
        Resource::TYPE::MODEL,
        Application::PATH_MODEL + "/GuildObject/TableSet.mv1"
    );
    resourcesMap_.emplace(SRC::TABLE_SET, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "/GuildStage/Request.png"
    );
    resourcesMap_.emplace(SRC::IMAGE_REQUEST, resource);

    resource = Resource(
        Resource::TYPE::MODEL,
        Application::PATH_MODEL + "GuildObject/uketuke.mv1"
    );
    resourcesMap_.emplace(SRC::RECEPTIONIST, resource);

    resource = Resource(
        Resource::TYPE::IMAGE,
        Application::PATH_IMAGE + "item/Seed.png"
    );
    resourcesMap_.emplace(SRC::SEED, resource);

    resource = Resource(
        Resource::TYPE::SOUND,
        Application::PATH_BGM + "maou_bgm_ethnic10.mp3"
    );
    resourcesMap_.emplace(SRC::BGM_GUILD, resource);
}

void ResourceManager::ResourceGarden(void)
{
    Resource resource;

    resource = Resource(
        Resource::TYPE::MODEL,
        Application::PATH_MODEL + "GardenObject/Block_Dirt.mv1"
    );
    resourcesMap_.emplace(SRC::BLOCK_DIRT, resource);

    resource = Resource(
        Resource::TYPE::MODEL,
        Application::PATH_MODEL + "GardenObject/Block_Grass.mv1"
    );
    resourcesMap_.emplace(SRC::BLOCK_GRASS, resource);

    resource = Resource(
        Resource::TYPE::MODEL,
        Application::PATH_MODEL + "GardenObject/Block_Lood.mv1"
    );
    resourcesMap_.emplace(SRC::BLOCK_ROAD, resource);

    resource = Resource(
        Resource::TYPE::MODEL,
        Application::PATH_MODEL + "GardenObject/Growing.mv1"
    );
    resourcesMap_.emplace(SRC::GROWING_MODEL, resource);

    resource = Resource(
        Resource::TYPE::MODEL,
        Application::PATH_MODEL + "GardenObject/Seed.mv1"
    );
    resourcesMap_.emplace(SRC::SEED_MODEL, resource);

    resource = Resource(
        Resource::TYPE::MODEL,
        Application::PATH_MODEL + "GardenObject/mature.mv1"
    );
    resourcesMap_.emplace(SRC::MATURE_MODEL, resource);

    resource = Resource(
        Resource::TYPE::MODEL,
        Application::PATH_MODEL + "GardenObject/ore.mv1"
    );
    resourcesMap_.emplace(SRC::ORE_MODEL, resource);

    resource = Resource(
        Resource::TYPE::MODEL,
        Application::PATH_MODEL + "GardenObject/fence.mv1"
    );
    resourcesMap_.emplace(SRC::FENCE_MODEL, resource);

    resource = Resource(
        Resource::TYPE::MODEL,
        Application::PATH_MODEL + "GardenObject/well.mv1"
    );
    resourcesMap_.emplace(SRC::WELL_MODEL, resource);

    resource = Resource(
        Resource::TYPE::MODEL,
        Application::PATH_MODEL + "GardenObject/Dowa.mv1"
    );
    resourcesMap_.emplace(SRC::DOOR_MODEL, resource);

    resource = Resource(
        Resource::TYPE::SOUND,
        Application::PATH_BGM + "nc86886.mp3"
    );
    resourcesMap_.emplace(SRC::BGM_GARDEN_DAY, resource);

    resource = Resource(
        Resource::TYPE::SOUND,
        Application::PATH_BGM + "nc141198_plant_girl.wav"
    );
    resourcesMap_.emplace(SRC::BGM_GARDEN_NIGHT, resource);
}

void ResourceManager::ResourcePlayer(void)
{
    Resource resource;

    resource = Resource(
        Resource::TYPE::MODEL,
        Application::PATH_MODEL + "player/player.mv1"
    );
    resourcesMap_.emplace(SRC::MODEL_PLAYER, resource);
}

void ResourceManager::ResourceEnemy(void)
{
}

void ResourceManager::Release(void)
{
    for (auto& loadedResource : loadedMap_)
    {
        loadedResource.second->Release();
        delete loadedResource.second;
    }

    loadedMap_.clear();
    resourcesMap_.clear();
}

void ResourceManager::Destroy(void)
{
    Release();
    delete instance_;
}

Resource ResourceManager::Load(SRC source)
{
    Resource* resource = LoadInternal(source);

    if (resource == nullptr)
    {
        return Resource();
    }

    return *resource;
}

int ResourceManager::LoadModelDuplicate(SRC source)
{
    Resource* resource = LoadInternal(source);

    if (resource == nullptr)
    {
        const int LOAD_FAILED = -1;
        return LOAD_FAILED;
    }

    int duplicateId = MV1DuplicateModel(resource->handleId_);
    resource->duplicateModelIds_.push_back(duplicateId);

    return duplicateId;
}

ResourceManager::ResourceManager(void)
{
}

Resource* ResourceManager::LoadInternal(SRC source)
{
    auto loadedIterator = loadedMap_.find(source);
    if (loadedIterator != loadedMap_.end())
    {
        return loadedIterator->second;
    }

    auto resourceIterator = resourcesMap_.find(source);
    if (resourceIterator == resourcesMap_.end())
    {
        return nullptr;
    }

    resourceIterator->second.Load();

    Resource* copiedResource = new Resource(resourceIterator->second);
    loadedMap_.emplace(source, copiedResource);

    return copiedResource;
}