#include "SkinChanger.h"

#include <array>
#include <format>
#include "../../utils/json.hpp"

enum ETFWeapons
{
	Scout_m_Scattergun = 13,
	Scout_m_ScattergunR = 200,
	Scout_m_ForceANature = 45,
	Scout_m_TheShortstop = 220,
	Scout_m_TheSodaPopper = 448,
	Scout_m_FestiveScattergun = 669,
	Scout_m_BabyFacesBlaster = 772,
	Scout_m_SilverBotkillerScattergunMkI = 799,
	Scout_m_GoldBotkillerScattergunMkI = 808,
	Scout_m_RustBotkillerScattergunMkI = 888,
	Scout_m_BloodBotkillerScattergunMkI = 897,
	Scout_m_CarbonadoBotkillerScattergunMkI = 906,
	Scout_m_DiamondBotkillerScattergunMkI = 915,
	Scout_m_SilverBotkillerScattergunMkII = 964,
	Scout_m_GoldBotkillerScattergunMkII = 973,
	Scout_m_FestiveForceANature = 1078,
	Scout_m_TheBackScatter = 1103,
	Scout_m_NightTerror = 15002,
	Scout_m_TartanTorpedo = 15015,
	Scout_m_CountryCrusher = 15021,
	Scout_m_BackcountryBlaster = 15029,
	Scout_m_SpruceDeuce = 15036,
	Scout_m_CurrentEvent = 15053,
	Scout_m_MacabreWeb = 15065,
	Scout_m_Nutcracker = 15069,
	Scout_m_BlueMew = 15106,
	Scout_m_FlowerPower = 15107,
	Scout_m_ShottoHell = 15108,
	Scout_m_CoffinNail = 15131,
	Scout_m_KillerBee = 15151,
	Scout_m_Corsair = 15157,
	Scout_s_ScoutsPistol = 23,
	Scout_s_PistolR = 209,
	Scout_s_BonkAtomicPunch = 46,
	Scout_s_VintageLugermorph = 160,
	Scout_s_CritaCola = 163,
	Scout_s_MadMilk = 222,
	Scout_s_Lugermorph = 294,
	Scout_s_TheWinger = 449,
	Scout_s_PrettyBoysPocketPistol = 773,
	Scout_s_TheFlyingGuillotine = 812,
	Scout_s_TheFlyingGuillotineG = 833,
	Scout_s_MutatedMilk = 1121,
	Scout_s_FestiveBonk = 1145,
	Scout_s_RedRockRoscoe = 15013,
	Scout_s_HomemadeHeater = 15018,
	Scout_s_HickoryHolepuncher = 15035,
	Scout_s_LocalHero = 15041,
	Scout_s_BlackDahlia = 15046,
	Scout_s_SandstoneSpecial = 15056,
	Scout_s_MacabreWeb = 15060,
	Scout_s_Nutcracker = 15061,
	Scout_s_BlueMew = 15100,
	Scout_s_BrainCandy = 15101,
	Scout_s_ShottoHell = 15102,
	Scout_s_DressedToKill = 15126,
	Scout_s_Blitzkrieg = 15148,
	Scout_s_TheCAPPER = 30666,
	Scout_t_Bat = 0,
	Scout_t_BatR = 190,
	Scout_t_TheSandman = 44,
	Scout_t_TheHolyMackerel = 221,
	Scout_t_TheCandyCane = 317,
	Scout_t_TheBostonBasher = 325,
	Scout_t_SunonaStick = 349,
	Scout_t_TheFanOWar = 355,
	Scout_t_TheAtomizer = 450,
	Scout_t_ThreeRuneBlade = 452,
	Scout_t_TheConscientiousObjector = 474,
	Scout_t_UnarmedCombat = 572,
	Scout_t_TheWrapAssassin = 648,
	Scout_t_FestiveBat = 660,
	Scout_t_TheFreedomStaff = 880,
	Scout_t_TheBatOuttaHell = 939,
	Scout_t_TheMemoryMaker = 954,
	Scout_t_FestiveHolyMackerel = 999,
	Scout_t_TheHamShank = 1013,
	Scout_t_TheNecroSmasher = 1123,
	Scout_t_TheCrossingGuard = 1127,
	Scout_t_Batsaber = 30667,
	Scout_t_PrinnyMachete = 30758,
	Soldier_m_RocketLauncher = 18,
	Soldier_m_RocketLauncherR = 205,
	Soldier_m_TheDirectHit = 127,
	Soldier_m_TheBlackBox = 228,
	Soldier_m_RocketJumper = 237,
	Soldier_m_TheLibertyLauncher = 414,
	Soldier_m_TheCowMangler5000 = 441,
	Soldier_m_TheOriginal = 513,
	Soldier_m_FestiveRocketLauncher = 658,
	Soldier_m_TheBeggarsBazooka = 730,
	Soldier_m_SilverBotkillerRocketLauncherMkI = 800,
	Soldier_m_GoldBotkillerRocketLauncherMkI = 809,
	Soldier_m_RustBotkillerRocketLauncherMkI = 889,
	Soldier_m_BloodBotkillerRocketLauncherMkI = 898,
	Soldier_m_CarbonadoBotkillerRocketLauncherMkI = 907,
	Soldier_m_DiamondBotkillerRocketLauncherMkI = 916,
	Soldier_m_SilverBotkillerRocketLauncherMkII = 965,
	Soldier_m_GoldBotkillerRocketLauncherMkII = 974,
	Soldier_m_FestiveBlackBox = 1085,
	Soldier_m_TheAirStrike = 1104,
	Soldier_m_WoodlandWarrior = 15006,
	Soldier_m_SandCannon = 15014,
	Soldier_m_AmericanPastoral = 15028,
	Soldier_m_SmalltownBringdown = 15043,
	Soldier_m_ShellShocker = 15052,
	Soldier_m_AquaMarine = 15057,
	Soldier_m_Autumn = 15081,
	Soldier_m_BlueMew = 15104,
	Soldier_m_BrainCandy = 15105,
	Soldier_m_CoffinNail = 15129,
	Soldier_m_HighRollers = 15130,
	Soldier_m_Warhawk = 15150,
	Soldier_s_SoldiersShotgun = 10,
	Soldier_s_ShotgunR = 199,
	Soldier_s_TheBuffBanner = 129,
	Soldier_s_Gunboats = 133,
	Soldier_s_TheBattalionsBackup = 226,
	Soldier_s_TheConcheror = 354,
	Soldier_s_TheReserveShooter = 415,
	Soldier_s_TheRighteousBison = 442,
	Soldier_s_TheMantreads = 444,
	Soldier_s_FestiveBuffBanner = 1001,
	Soldier_s_TheBASEJumper = 1101,
	Soldier_s_FestiveShotgun = 1141,
	Soldier_s_PanicAttack = 1153,
	Soldier_s_BackwoodsBoomstick = 15003,
	Soldier_s_RusticRuiner = 15016,
	Soldier_s_CivicDuty = 15044,
	Soldier_s_LightningRod = 15047,
	Soldier_s_Autumn = 15085,
	Soldier_s_FlowerPower = 15109,
	Soldier_s_CoffinNail = 15132,
	Soldier_s_DressedtoKill = 15133,
	Soldier_s_RedBear = 15152,
	Soldier_t_Shovel = 6,
	Soldier_t_ShovelR = 196,
	Soldier_t_TheEqualizer = 128,
	Soldier_t_ThePainTrain = 154,
	Soldier_t_TheHalfZatoichi = 357,
	Soldier_t_TheMarketGardener = 416,
	Soldier_t_TheDisciplinaryAction = 447,
	Soldier_t_TheConscientiousObjector = 474,
	Soldier_t_TheEscapePlan = 775,
	Soldier_t_TheFreedomStaff = 880,
	Soldier_t_TheBatOuttaHell = 939,
	Soldier_t_TheMemoryMaker = 954,
	Soldier_t_TheHamShank = 1013,
	Soldier_t_TheNecroSmasher = 1123,
	Soldier_t_TheCrossingGuard = 1127,
	Soldier_t_PrinnyMachete = 30758,
	Pyro_m_FlameThrower = 21,
	Pyro_m_FlameThrowerR = 208,
	Pyro_m_TheBackburner = 40,
	Pyro_m_TheDegreaser = 215,
	Pyro_m_ThePhlogistinator = 594,
	Pyro_m_FestiveFlameThrower = 659,
	Pyro_m_TheRainblower = 741,
	Pyro_m_SilverBotkillerFlameThrowerMkI = 798,
	Pyro_m_GoldBotkillerFlameThrowerMkI = 807,
	Pyro_m_RustBotkillerFlameThrowerMkI = 887,
	Pyro_m_BloodBotkillerFlameThrowerMkI = 896,
	Pyro_m_CarbonadoBotkillerFlameThrowerMkI = 905,
	Pyro_m_DiamondBotkillerFlameThrowerMkI = 914,
	Pyro_m_SilverBotkillerFlameThrowerMkII = 963,
	Pyro_m_GoldBotkillerFlameThrowerMkII = 972,
	Pyro_m_FestiveBackburner = 1146,
	Pyro_m_DragonsFury = 1178,
	Pyro_m_ForestFire = 15005,
	Pyro_m_BarnBurner = 15017,
	Pyro_m_BovineBlazemaker = 15030,
	Pyro_m_EarthSkyandFire = 15034,
	Pyro_m_FlashFryer = 15049,
	Pyro_m_TurbineTorcher = 15054,
	Pyro_m_Autumn = 15066,
	Pyro_m_PumpkinPatch = 15067,
	Pyro_m_Nutcracker = 15068,
	Pyro_m_Balloonicorn = 15089,
	Pyro_m_Rainbow = 15090,
	Pyro_m_CoffinNail = 15115,
	Pyro_m_Warhawk = 15141,
	Pyro_m_NostromoNapalmer = 30474,
	Pyro_s_PyrosShotgun = 12,
	Pyro_s_ShotgunR = 199,
	Pyro_s_TheFlareGun = 39,
	Pyro_s_TheDetonator = 351,
	Pyro_s_TheReserveShooter = 415,
	Pyro_s_TheManmelter = 595,
	Pyro_s_TheScorchShot = 740,
	Pyro_s_FestiveFlareGun = 1081,
	Pyro_s_FestiveShotgun = 1141,
	Pyro_s_PanicAttack = 1153,
	Pyro_s_ThermalThruster = 1179,
	Pyro_s_GasPasser = 1180,
	Pyro_s_BackwoodsBoomstick = 15003,
	Pyro_s_RusticRuiner = 15016,
	Pyro_s_CivicDuty = 15044,
	Pyro_s_LightningRod = 15047,
	Pyro_s_Autumn = 15085,
	Pyro_s_FlowerPower = 15109,
	Pyro_s_CoffinNail = 15132,
	Pyro_s_DressedtoKill = 15133,
	Pyro_s_RedBear = 15152,
	Pyro_t_FireAxe = 2,
	Pyro_t_FireAxeR = 192,
	Pyro_t_TheAxtinguisher = 38,
	Pyro_t_Homewrecker = 153,
	Pyro_t_ThePowerjack = 214,
	Pyro_t_TheBackScratcher = 326,
	Pyro_t_SharpenedVolcanoFragment = 348,
	Pyro_t_ThePostalPummeler = 457,
	Pyro_t_TheMaul = 466,
	Pyro_t_TheConscientiousObjector = 474,
	Pyro_t_TheThirdDegree = 593,
	Pyro_t_TheLollichop = 739,
	Pyro_t_NeonAnnihilator = 813,
	Pyro_t_NeonAnnihilatorG = 834,
	Pyro_t_TheFreedomStaff = 880,
	Pyro_t_TheBatOuttaHell = 939,
	Pyro_t_TheMemoryMaker = 954,
	Pyro_t_TheFestiveAxtinguisher = 1000,
	Pyro_t_TheHamShank = 1013,
	Pyro_t_TheNecroSmasher = 1123,
	Pyro_t_TheCrossingGuard = 1127,
	Pyro_t_HotHand = 1181,
	Pyro_t_PrinnyMachete = 30758,
	Demoman_m_GrenadeLauncher = 19,
	Demoman_m_GrenadeLauncherR = 206,
	Demoman_m_TheLochnLoad = 308,
	Demoman_m_AliBabasWeeBooties = 405,
	Demoman_m_TheBootlegger = 608,
	Demoman_m_TheLooseCannon = 996,
	Demoman_m_FestiveGrenadeLauncher = 1007,
	Demoman_m_TheBASEJumper = 1101,
	Demoman_m_TheIronBomber = 1151,
	Demoman_m_Autumn = 15077,
	Demoman_m_MacabreWeb = 15079,
	Demoman_m_Rainbow = 15091,
	Demoman_m_SweetDreams = 15092,
	Demoman_m_CoffinNail = 15116,
	Demoman_m_TopShelf = 15117,
	Demoman_m_Warhawk = 15142,
	Demoman_m_ButcherBird = 15158,
	Demoman_s_StickybombLauncher = 20,
	Demoman_s_StickybombLauncherR = 207,
	Demoman_s_TheScottishResistance = 130,
	Demoman_s_TheCharginTarge = 131,
	Demoman_s_StickyJumper = 265,
	Demoman_s_TheSplendidScreen = 406,
	Demoman_s_FestiveStickybombLauncher = 661,
	Demoman_s_SilverBotkillerStickybombLauncherMkI = 797,
	Demoman_s_GoldBotkillerStickybombLauncherMkI = 806,
	Demoman_s_RustBotkillerStickybombLauncherMkI = 886,
	Demoman_s_BloodBotkillerStickybombLauncherMkI = 895,
	Demoman_s_CarbonadoBotkillerStickybombLauncherMkI = 904,
	Demoman_s_DiamondBotkillerStickybombLauncherMkI = 913,
	Demoman_s_SilverBotkillerStickybombLauncherMkII = 962,
	Demoman_s_GoldBotkillerStickybombLauncherMkII = 971,
	Demoman_s_TheTideTurner = 1099,
	Demoman_s_FestiveTarge = 1144,
	Demoman_s_TheQuickiebombLauncher = 1150,
	Demoman_s_SuddenFlurry = 15009,
	Demoman_s_CarpetBomber = 15012,
	Demoman_s_BlastedBombardier = 15024,
	Demoman_s_RooftopWrangler = 15038,
	Demoman_s_LiquidAsset = 15045,
	Demoman_s_PinkElephant = 15048,
	Demoman_s_Autumn = 15082,
	Demoman_s_PumpkinPatch = 15083,
	Demoman_s_MacabreWeb = 15084,
	Demoman_s_SweetDreams = 15113,
	Demoman_s_CoffinNail = 15137,
	Demoman_s_DressedtoKill = 15138,
	Demoman_s_Blitzkrieg = 15155,
	Demoman_t_Bottle = 1,
	Demoman_t_BottleR = 191,
	Demoman_t_TheEyelander = 132,
	Demoman_t_ThePainTrain = 154,
	Demoman_t_TheScotsmansSkullcutter = 172,
	Demoman_t_HorselessHeadlessHorsemannsHeadtaker = 266,
	Demoman_t_UllapoolCaber = 307,
	Demoman_t_TheClaidheamhMor = 327,
	Demoman_t_TheHalfZatoichi = 357,
	Demoman_t_ThePersianPersuader = 404,
	Demoman_t_TheConscientiousObjector = 474,
	Demoman_t_NessiesNineIron = 482,
	Demoman_t_TheScottishHandshake = 609,
	Demoman_t_TheFreedomStaff = 880,
	Demoman_t_TheBatOuttaHell = 939,
	Demoman_t_TheMemoryMaker = 954,
	Demoman_t_TheHamShank = 1013,
	Demoman_t_FestiveEyelander = 1082,
	Demoman_t_TheNecroSmasher = 1123,
	Demoman_t_TheCrossingGuard = 1127,
	Demoman_t_PrinnyMachete = 30758,
	Heavy_m_Minigun = 15,
	Heavy_m_MinigunR = 202,
	Heavy_m_Natascha = 41,
	Heavy_m_IronCurtain = 298,
	Heavy_m_TheBrassBeast = 312,
	Heavy_m_Tomislav = 424,
	Heavy_m_FestiveMinigun = 654,
	Heavy_m_SilverBotkillerMinigunMkI = 793,
	Heavy_m_GoldBotkillerMinigunMkI = 802,
	Heavy_m_TheHuoLongHeater = 811,
	Heavy_m_TheHuoLongHeaterG = 832,
	Heavy_m_Deflector_mvm = 850,
	Heavy_m_RustBotkillerMinigunMkI = 882,
	Heavy_m_BloodBotkillerMinigunMkI = 891,
	Heavy_m_CarbonadoBotkillerMinigunMkI = 900,
	Heavy_m_DiamondBotkillerMinigunMkI = 909,
	Heavy_m_SilverBotkillerMinigunMkII = 958,
	Heavy_m_GoldBotkillerMinigunMkII = 967,
	Heavy_m_KingoftheJungle = 15004,
	Heavy_m_IronWood = 15020,
	Heavy_m_AntiqueAnnihilator = 15026,
	Heavy_m_WarRoom = 15031,
	Heavy_m_CitizenPain = 15040,
	Heavy_m_BrickHouse = 15055,
	Heavy_m_MacabreWeb = 15086,
	Heavy_m_PumpkinPatch = 15087,
	Heavy_m_Nutcracker = 15088,
	Heavy_m_BrainCandy = 15098,
	Heavy_m_MisterCuddles = 15099,
	Heavy_m_CoffinNail = 15123,
	Heavy_m_DressedtoKill = 15124,
	Heavy_m_TopShelf = 15125,
	Heavy_m_ButcherBird = 15147,
	Heavy_s_HeavysShotgun = 11,
	Heavy_s_ShotgunR = 199,
	Heavy_s_Sandvich = 42,
	Heavy_s_TheDalokohsBar = 159,
	Heavy_s_TheBuffaloSteakSandvich = 311,
	Heavy_s_TheFamilyBusiness = 425,
	Heavy_s_Fishcake = 433,
	Heavy_s_RoboSandvich = 863,
	Heavy_s_FestiveSandvich = 1002,
	Heavy_s_FestiveShotgun = 1141,
	Heavy_s_PanicAttack = 1153,
	Heavy_s_SecondBanana = 1190,
	Heavy_s_BackwoodsBoomstick = 15003,
	Heavy_s_RusticRuiner = 15016,
	Heavy_s_CivicDuty = 15044,
	Heavy_s_LightningRod = 15047,
	Heavy_s_Autumn = 15085,
	Heavy_s_FlowerPower = 15109,
	Heavy_s_CoffinNail = 15132,
	Heavy_s_DressedtoKill = 15133,
	Heavy_s_RedBear = 15152,
	Heavy_t_Fists = 5,
	Heavy_t_FistsR = 195,
	Heavy_t_TheKillingGlovesofBoxing = 43,
	Heavy_t_GlovesofRunningUrgently = 239,
	Heavy_t_WarriorsSpirit = 310,
	Heavy_t_FistsofSteel = 331,
	Heavy_t_TheEvictionNotice = 426,
	Heavy_t_TheConscientiousObjector = 474,
	Heavy_t_ApocoFists = 587,
	Heavy_t_TheHolidayPunch = 656,
	Heavy_t_TheFreedomStaff = 880,
	Heavy_t_TheBatOuttaHell = 939,
	Heavy_t_TheMemoryMaker = 954,
	Heavy_t_TheHamShank = 1013,
	Heavy_t_FestiveGlovesofRunningUrgently = 1084,
	Heavy_t_TheBreadBite = 1100,
	Heavy_t_TheNecroSmasher = 1123,
	Heavy_t_TheCrossingGuard = 1127,
	Heavy_t_GlovesofRunningUrgentlyMvM = 1184,
	Heavy_t_PrinnyMachete = 30758,
	Engi_m_EngineersShotgun = 9,
	Engi_m_ShotgunR = 199,
	Engi_m_TheFrontierJustice = 141,
	Engi_m_TheWidowmaker = 527,
	Engi_m_ThePomson6000 = 588,
	Engi_m_TheRescueRanger = 997,
	Engi_m_FestiveFrontierJustice = 1004,
	Engi_m_FestiveShotgun = 1141,
	Engi_m_PanicAttack = 1153,
	Engi_m_BackwoodsBoomstick = 15003,
	Engi_m_RusticRuiner = 15016,
	Engi_m_CivicDuty = 15044,
	Engi_m_LightningRod = 15047,
	Engi_m_Autumn = 15085,
	Engi_m_FlowerPower = 15109,
	Engi_m_CoffinNail = 15132,
	Engi_m_DressedtoKill = 15133,
	Engi_m_RedBear = 15152,
	Engi_s_EngineersPistol = 22,
	Engi_s_PistolR = 209,
	Engi_s_TheWrangler = 140,
	Engi_s_VintageLugermorph = 160,
	Engi_s_Lugermorph = 294,
	Engi_s_TheShortCircuit = 528,
	Engi_s_FestiveWrangler = 1086,
	Engi_s_RedRockRoscoe = 15013,
	Engi_s_HomemadeHeater = 15018,
	Engi_s_HickoryHolepuncher = 15035,
	Engi_s_LocalHero = 15041,
	Engi_s_BlackDahlia = 15046,
	Engi_s_SandstoneSpecial = 15056,
	Engi_s_MacabreWeb = 15060,
	Engi_s_Nutcracker = 15061,
	Engi_s_BlueMew = 15100,
	Engi_s_BrainCandy = 15101,
	Engi_s_ShottoHell = 15102,
	Engi_s_DressedToKill = 15126,
	Engi_s_Blitzkrieg = 15148,
	Engi_s_TheCAPPER = 30666,
	Engi_s_TheGigarCounter = 30668,
	Engi_t_Wrench = 7,
	Engi_t_WrenchR = 197,
	Engi_t_TheGunslinger = 142,
	Engi_t_TheSouthernHospitality = 155,
	Engi_t_GoldenWrench = 169,
	Engi_t_TheJag = 329,
	Engi_t_TheEurekaEffect = 589,
	Engi_t_FestiveWrench = 662,
	Engi_t_SilverBotkillerWrenchMkI = 795,
	Engi_t_GoldBotkillerWrenchMkI = 804,
	Engi_t_RustBotkillerWrenchMkI = 884,
	Engi_t_BloodBotkillerWrenchMkI = 893,
	Engi_t_CarbonadoBotkillerWrenchMkI = 902,
	Engi_t_DiamondBotkillerWrenchMkI = 911,
	Engi_t_SilverBotkillerWrenchMkII = 960,
	Engi_t_GoldBotkillerWrenchMkII = 969,
	Engi_t_TheNecroSmasher = 1123,
	Engi_t_Nutcracker = 15073,
	Engi_t_Autumn = 15074,
	Engi_t_Boneyard = 15075,
	Engi_t_DressedtoKill = 15139,
	Engi_t_TopShelf = 15140,
	Engi_t_TorquedtoHell = 15114,
	Engi_t_Airwolf = 15156,
	Engi_t_PrinnyMachete = 30758,
	Engi_p_ConstructionPDA = 25,
	Engi_p_ConstructionPDAR = 737,
	Engi_p_DestructionPDA = 26,
	Engi_p_PDA = 28,
	Medic_m_SyringeGun = 17,
	Medic_m_SyringeGunR = 204,
	Medic_m_TheBlutsauger = 36,
	Medic_m_CrusadersCrossbow = 305,
	Medic_m_TheOverdose = 412,
	Medic_m_FestiveCrusadersCrossbow = 1079,
	Medic_s_MediGun = 29,
	Medic_s_MediGunR = 211,
	Medic_s_TheKritzkrieg = 35,
	Medic_s_TheQuickFix = 411,
	Medic_s_FestiveMediGun = 663,
	Medic_s_SilverBotkillerMediGunMkI = 796,
	Medic_s_GoldBotkillerMediGunMkI = 805,
	Medic_s_RustBotkillerMediGunMkI = 885,
	Medic_s_BloodBotkillerMediGunMkI = 894,
	Medic_s_CarbonadoBotkillerMediGunMkI = 903,
	Medic_s_DiamondBotkillerMediGunMkI = 912,
	Medic_s_SilverBotkillerMediGunMkII = 961,
	Medic_s_GoldBotkillerMediGunMkII = 970,
	Medic_s_TheVaccinator = 998,
	Medic_s_MaskedMender = 15008,
	Medic_s_WrappedReviver = 15010,
	Medic_s_ReclaimedReanimator = 15025,
	Medic_s_CivilServant = 15039,
	Medic_s_SparkofLife = 15050,
	Medic_s_Wildwood = 15078,
	Medic_s_FlowerPower = 15097,
	Medic_s_DressedToKill = 15121,
	Medic_s_HighRollers = 15122,
	Medic_s_CoffinNail = 15123,
	Medic_s_Blitzkrieg = 15145,
	Medic_s_Corsair = 15146,
	Medic_t_Bonesaw = 8,
	Medic_t_BonesawR = 198,
	Medic_t_TheUbersaw = 37,
	Medic_t_TheVitaSaw = 173,
	Medic_t_Amputator = 304,
	Medic_t_TheSolemnVow = 413,
	Medic_t_TheConscientiousObjector = 474,
	Medic_t_TheFreedomStaff = 880,
	Medic_t_TheBatOuttaHell = 939,
	Medic_t_TheMemoryMaker = 954,
	Medic_t_FestiveUbersaw = 1003,
	Medic_t_TheHamShank = 1013,
	Medic_t_TheNecroSmasher = 1123,
	Medic_t_TheCrossingGuard = 1127,
	Medic_t_FestiveBonesaw = 1143,
	Medic_t_PrinnyMachete = 30758,
	Sniper_m_SniperRifle = 14,
	Sniper_m_SniperRifleR = 201,
	Sniper_m_TheHuntsman = 56,
	Sniper_m_TheSydneySleeper = 230,
	Sniper_m_TheBazaarBargain = 402,
	Sniper_m_TheMachina = 526,
	Sniper_m_FestiveSniperRifle = 664,
	Sniper_m_TheHitmansHeatmaker = 752,
	Sniper_m_SilverBotkillerSniperRifleMkI = 792,
	Sniper_m_GoldBotkillerSniperRifleMkI = 801,
	Sniper_m_TheAWPerHand = 851,
	Sniper_m_RustBotkillerSniperRifleMkI = 881,
	Sniper_m_BloodBotkillerSniperRifleMkI = 890,
	Sniper_m_CarbonadoBotkillerSniperRifleMkI = 899,
	Sniper_m_DiamondBotkillerSniperRifleMkI = 908,
	Sniper_m_SilverBotkillerSniperRifleMkII = 957,
	Sniper_m_GoldBotkillerSniperRifleMkII = 966,
	Sniper_m_FestiveHuntsman = 1005,
	Sniper_m_TheFortifiedCompound = 1092,
	Sniper_m_TheClassic = 1098,
	Sniper_m_NightOwl = 15000,
	Sniper_m_PurpleRange = 15007,
	Sniper_m_LumberFromDownUnder = 15019,
	Sniper_m_ShotintheDark = 15023,
	Sniper_m_Bogtrotter = 15033,
	Sniper_m_Thunderbolt = 15059,
	Sniper_m_PumpkinPatch = 15070,
	Sniper_m_Boneyard = 15071,
	Sniper_m_Wildwood = 15072,
	Sniper_m_Balloonicorn = 15111,
	Sniper_m_Rainbow = 15112,
	Sniper_m_CoffinNail = 15135,
	Sniper_m_DressedtoKill = 15136,
	Sniper_m_Airwolf = 15154,
	Sniper_m_ShootingStar = 30665,
	Sniper_s_SMG = 16,
	Sniper_s_SMGR = 203,
	Sniper_s_TheRazorback = 57,
	Sniper_s_Jarate = 58,
	Sniper_s_DarwinsDangerShield = 231,
	Sniper_s_CozyCamper = 642,
	Sniper_s_TheCleanersCarbine = 751,
	Sniper_s_FestiveJarate = 1083,
	Sniper_s_TheSelfAwareBeautyMark = 1105,
	Sniper_s_FestiveSMG = 1149,
	Sniper_s_WoodsyWidowmaker = 15001,
	Sniper_s_PlaidPotshotter = 15022,
	Sniper_s_TreadplateTormenter = 15032,
	Sniper_s_TeamSprayer = 15037,
	Sniper_s_LowProfile = 15058,
	Sniper_s_Wildwood = 15076,
	Sniper_s_BlueMew = 15110,
	Sniper_s_HighRollers = 15134,
	Sniper_s_Blitzkrieg = 15153,
	Sniper_t_Kukri = 3,
	Sniper_t_KukriR = 193,
	Sniper_t_TheTribalmansShiv = 171,
	Sniper_t_TheBushwacka = 232,
	Sniper_t_TheShahanshah = 401,
	Sniper_t_TheConscientiousObjector = 474,
	Sniper_t_TheFreedomStaff = 880,
	Sniper_t_TheBatOuttaHell = 939,
	Sniper_t_TheMemoryMaker = 954,
	Sniper_t_TheHamShank = 1013,
	Sniper_t_TheNecroSmasher = 1123,
	Sniper_t_TheCrossingGuard = 1127,
	Sniper_t_PrinnyMachete = 30758,
	Spy_m_Revolver = 24,
	Spy_m_RevolverR = 210,
	Spy_m_TheAmbassador = 61,
	Spy_m_BigKill = 161,
	Spy_m_LEtranger = 224,
	Spy_m_TheEnforcer = 460,
	Spy_m_TheDiamondback = 525,
	Spy_m_FestiveAmbassador = 1006,
	Spy_m_FestiveRevolver = 1142,
	Spy_m_PsychedelicSlugger = 15011,
	Spy_m_OldCountry = 15027,
	Spy_m_Mayor = 15042,
	Spy_m_DeadReckoner = 15051,
	Spy_m_Boneyard = 15062,
	Spy_m_Wildwood = 15063,
	Spy_m_MacabreWeb = 15064,
	Spy_m_FlowerPower = 15103,
	Spy_m_TopShelf = 15128,
	Spy_m_CoffinNail = 15129,
	Spy_m_Blitzkrieg = 15149,
	Spy_s_Sapper = 735,
	Spy_s_SapperR = 736,
	Spy_s_TheRedTapeRecorder = 810,
	Spy_s_TheRedTapeRecorderG = 831,
	Spy_s_TheApSapG = 933,
	Spy_s_FestiveSapper = 1080,
	Spy_s_TheSnackAttack = 1102,
	Spy_t_Knife = 4,
	Spy_t_KnifeR = 194,
	Spy_t_YourEternalReward = 225,
	Spy_t_ConniversKunai = 356,
	Spy_t_TheBigEarner = 461,
	Spy_t_TheWangaPrick = 574,
	Spy_t_TheSharpDresser = 638,
	Spy_t_TheSpycicle = 649,
	Spy_t_FestiveKnife = 665,
	Spy_t_TheBlackRose = 727,
	Spy_t_SilverBotkillerKnifeMkI = 794,
	Spy_t_GoldBotkillerKnifeMkI = 803,
	Spy_t_RustBotkillerKnifeMkI = 883,
	Spy_t_BloodBotkillerKnifeMkI = 892,
	Spy_t_CarbonadoBotkillerKnifeMkI = 901,
	Spy_t_DiamondBotkillerKnifeMkI = 910,
	Spy_t_SilverBotkillerKnifeMkII = 959,
	Spy_t_GoldBotkillerKnifeMkII = 968,
	Spy_t_Boneyard = 15062,
	Spy_t_BlueMew = 15094,
	Spy_t_BrainCandy = 15095,
	Spy_t_StabbedtoHell = 15096,
	Spy_t_DressedtoKill = 15118,
	Spy_t_TopShelf = 15119,
	Spy_t_Blitzkrieg = 15143,
	Spy_t_Airwolf = 15144,
	Spy_t_PrinnyMachete = 30758,
	Spy_d_DisguiseKitPDA = 27,
	Spy_w_InvisWatch = 30,
	Spy_w_InvisWatchR = 212,
	Spy_w_TheDeadRinger = 59,
	Spy_w_TheCloakandDagger = 60,
	Spy_w_EnthusiastsTimepiece = 297,
	Spy_w_TheQuackenbirdt = 947,
	Misc_t_FryingPan = 264,
	Misc_t_GoldFryingPan = 1071,
	Misc_t_Saxxy = 423,
};

#ifndef _WIN64
SIGNATURE(GetItemSchema, "client.dll", "E8 ? ? ? ? 83 C0 ? C3 CC");
SIGNATURE(CEconItemSchema_GetAttributeDefinition, "client.dll", "55 8B EC 83 EC ? 53 56 8B D9 8D 4D ? 57 E8 ? ? ? ? 8B 45");
SIGNATURE(CAttributeList_SetRuntimeAttributeValue, "client.dll", "55 8B EC 83 EC ? 33 C0 53 8B D9 56 57 8B 7D");
#else
SIGNATURE(GetItemSchema, "client.dll", "48 83 EC ? E8 ? ? ? ? 48 83 C0 ? 48 83 C4 ? C3 CC CC CC");
SIGNATURE(CEconItemSchema_GetAttributeDefinition, "client.dll", "89 54 24 ? 53 48 83 EC ? 48 8B D9 48 8D 54 24 ? 48 81 C1 ? ? ? ? E8 ? ? ? ? 8B D0 3B 83 ? ? ? ? 73 ? 8B 83 ? ? ? ? 83 F8 ? 74 ? 3B D0 7F ? 48 81 C3 ? ? ? ? 44 8B C2 83 FA ? 74 ? 48 8B 03 8B CA");
SIGNATURE(CAttributeList_SetRuntimeAttributeValue, "client.dll", "48 89 5C 24 10 55 56 57 48 8B EC 48 83 EC 50 44");
#endif

/*
m_iAttributeDefinitionIndex = 0x8
m_iRawValue32 = 0x12
m_flValue = 0x12
m_nRefundableCurrency = 0x16
*/

class CEconItemAttribute
{
public:
	void* pad = 0;
#ifndef _WIN64
	uint16_t m_iAttributeDefinitionIndex;
#else
	unsigned int m_iAttributeDefinitionIndex;
#endif
	union
	{
		int m_iRawValue32;
		float m_flValue;
	};
	int m_nRefundableCurrency = 0;

	inline CEconItemAttribute(uint16_t iAttributeDefinitionIndex, float flValue)
	{
		m_iAttributeDefinitionIndex = iAttributeDefinitionIndex;
		m_flValue = flValue;
	}
};

class CAttributeList
{
public:
	void* pad;
	CUtlVector<CEconItemAttribute, CUtlMemory<CEconItemAttribute>> m_Attributes;
	void* m_pManager;

	inline void AddAttribute(int iIndex, float flValue)
	{
		if (m_Attributes.Count() > 14)
			return;

		CEconItemAttribute attr(iIndex, flValue);

		m_Attributes.AddToTail(attr);
	}

#ifndef _WIN64
	using GetItemSchemaFN = void* (__cdecl*)();
	using GetAttributeDefinitionFN = void* (__thiscall*)(void*, int);
	using SetRuntimeAttributeValueFN = void(__thiscall*)(CAttributeList*, void*, float);
#else
	using GetItemSchemaFN = void* (__fastcall*)();
	using GetAttributeDefinitionFN = void* (__fastcall*)(void*, int);
	using SetRuntimeAttributeValueFN = void(__fastcall*)(CAttributeList*, void*, float);
#endif

	void SetAttribute(int index, float value)
	{
		auto schema = reinterpret_cast<GetItemSchemaFN>(Sigs::GetItemSchema.Get())();

		auto attributeDefinition = reinterpret_cast<GetAttributeDefinitionFN>(Sigs::CEconItemSchema_GetAttributeDefinition.Get())(schema, index);
		if (!attributeDefinition)
			return;

		reinterpret_cast<SetRuntimeAttributeValueFN>(Sigs::CAttributeList_SetRuntimeAttributeValue.Get())(this, attributeDefinition, value);
	}
};

#define Redirect(from, to) case from: { nWeaponIndex = to; break; }

void SkinChanger::RedirectIndex(int& nWeaponIndex)
{
	switch (nWeaponIndex)
	{
		//Redirect(Misc_t_FryingPan, Misc_t_GoldFryingPan);
		Redirect(Soldier_m_RocketLauncher, Soldier_m_RocketLauncherR);
		Redirect(Scout_m_Scattergun, Scout_m_ScattergunR);
		Redirect(Pyro_m_FlameThrower, Pyro_m_FlameThrowerR);
		Redirect(Demoman_m_GrenadeLauncher, Demoman_m_GrenadeLauncherR);
		Redirect(Demoman_s_StickybombLauncher, Demoman_s_StickybombLauncherR);
		Redirect(Heavy_m_Minigun, Heavy_m_MinigunR);
		Redirect(Engi_t_Wrench, Engi_t_WrenchR);
		Redirect(Medic_s_MediGun, Medic_s_MediGunR);
		Redirect(Sniper_m_SniperRifle, Sniper_m_SniperRifleR);
		Redirect(Sniper_s_SMG, Sniper_s_SMGR);
		Redirect(Spy_t_Knife, Spy_t_KnifeR);
		Redirect(Spy_m_Revolver, Spy_m_RevolverR);
		Redirect(Engi_s_EngineersPistol, Engi_s_PistolR);
		Redirect(Soldier_s_SoldiersShotgun, Soldier_s_ShotgunR);
		Redirect(Pyro_s_PyrosShotgun, Pyro_s_ShotgunR);
		Redirect(Heavy_s_HeavysShotgun, Heavy_s_ShotgunR);
		Redirect(Engi_m_EngineersShotgun, Engi_m_ShotgunR);
		Redirect(Scout_t_Bat, Scout_t_BatR);
		Redirect(Soldier_t_Shovel, Soldier_t_ShovelR);
		Redirect(Pyro_t_FireAxe, Pyro_t_FireAxeR);
		Redirect(Demoman_t_Bottle, Demoman_t_BottleR);
		Redirect(Medic_t_Bonesaw, Medic_t_BonesawR);
		Redirect(Sniper_t_Kukri, Sniper_t_KukriR);
		default: break;
	}
}

void SkinChanger::ApplySkin(Weapon* pWeapon)
{
	if (!pWeapon)
		return;

	int& nWeaponIndex = pWeapon->m_iItemDefinitionIndex();
	RedirectIndex(nWeaponIndex);

#ifndef _WIN64
	auto attributeList = reinterpret_cast<CAttributeList*>(reinterpret_cast<std::uintptr_t>(pWeapon) + 0x9C4);
#else
	auto attributeList = reinterpret_cast<CAttributeList*>(reinterpret_cast<std::uintptr_t>(pWeapon) + 3512);
#endif
	if (!attributeList)
		return;

#ifdef _DEBUG
		if (attributeList->m_Attributes.Count() > 0 && m_Skins.find(nWeaponIndex) == m_Skins.end())
	{
		// This weapon seems to already have a skin applied, but we don't have it in our map
		// Let's print out what attributes it has
		std::cout << "Weapon that needs to have different pre-filled attributes: " << nWeaponIndex << std::endl;

		for (const auto& attribute : attributeList->m_Attributes)
		{
			std::cout << "Attribute: " << attribute.m_iAttributeDefinitionIndex << " Value: " << attribute.m_flValue << std::endl;
		}
	}
#endif

	auto PreFilledAttributeCount = [&](int index) -> int
		{
			// Most weapons have no attributes, some have more than one.
			// Seems all snipers have this "no_jump" attribute
			switch (index)
			{
				case Sniper_m_TheBazaarBargain:
				case Sniper_m_SniperRifle:
				case Sniper_m_SniperRifleR:
					return 1;

				default: return 0;
			}
		};

		// If we have attributes, we've already applied all the attributes we want
	if (attributeList->m_Attributes.Count() > PreFilledAttributeCount(m_nCurrentWeaponIndex))
		return;

	// Not a weapon we plan to add attributes to
	if (m_Skins.find(nWeaponIndex) == m_Skins.end())
		return;

	// Apply the attributes if we have requested attributes for it
	const auto& vecAttributes = m_Skins[nWeaponIndex].m_Attributes;
	if (vecAttributes.empty())
		return;

	for (const auto& attribute : vecAttributes)
		attributeList->SetAttribute(attribute.attributeIndex, attribute.attributeValue);
}

void SkinChanger::ApplySkins()
{
	if (!m_bInitialSkinLoad)
	{
		Load();
		m_bInitialSkinLoad = true;
	}

	auto pLocal = (Player*)I::EntityList->GetClientEntity(I::EngineClient->GetLocalPlayer());
	if (!pLocal)
		return;

	auto pWeapon = pLocal->m_hActiveWeapon().Get();
	if (m_bForceFullUpdate)
	{
		I::ClientState->ForceFullUpdate();
		m_bForceFullUpdate = false;
	}

	if (!pWeapon)
		return;

	int& nWeaponIndex = pWeapon->m_iItemDefinitionIndex();
	RedirectIndex(nWeaponIndex);

	m_nCurrentWeaponIndex = nWeaponIndex;

	const auto& m_hMyWeapons = pLocal->m_hMyWeapons();
	for (int i = 0; m_hMyWeapons[i].IsValid(); i++)
	{
		auto pWeapon = m_hMyWeapons[i].Get();
		if (!pWeapon)
			continue;

		ApplySkin(pWeapon);
	}
}

void SkinChanger::SetAttribute(int index, std::string attributeStr, float value)
{
	if (index == -1)
		return;

	uint16_t attributeIndex = attributes::StringToAttribute(attributeStr);

	if (attributeIndex == attributes::paintkit_proto_def_index)
		value = IntToStupidFloat(static_cast<int>(value));

	if (m_Skins.find(index) == m_Skins.end())
		m_Skins[index] = SkinInfo();

	// Check if attribute already exists, if so, update it
	bool bFound = false;

	for (auto& attribute : m_Skins[index].m_Attributes)
	{
		if (attribute.attributeIndex == attributeIndex)
		{
			attribute.attributeValue = value;

			bFound = true;
			break;
		}
	}

	if (!bFound)// Attribute doesn't exist, add it
		m_Skins[index].m_Attributes.push_back({ attributeIndex, value });

	m_bForceFullUpdate = true;
}

void SkinChanger::RemoveAttribute(int index, std::string attributeStr)
{
	if (m_Skins.find(index) == m_Skins.end())
		return;

	auto& attributes = m_Skins[index].m_Attributes;

	uint16_t attributeIndex = attributes::StringToAttribute(attributeStr);

	// Find attribute
	for (auto it = attributes.begin(); it != attributes.end(); ++it)
	{
		if (it->attributeIndex == attributeIndex)
		{
			attributes.erase(it);
			m_bForceFullUpdate = true;

			return;
		}
	}
}

void SkinChanger::Save()
{
	std::ofstream file("skins.json");
	if (!file.good())
		return;

	nlohmann::json j;

	for (const auto& skin : m_Skins)
	{
		int index = skin.first;
		if (index == -1)
			continue;

		const auto& vecAttributes = skin.second.m_Attributes;
		std::string strIndex = std::to_string(index);

		for (const auto& attribute : vecAttributes)
		{
			j[strIndex][std::to_string(attribute.attributeIndex)] = attribute.attributeValue;
		}
	}

	file << j.dump(4);

	file.close();
}

void SkinChanger::Load()
{
	std::ifstream file("skins.json");
	if (!file.good())
		return;

	m_Skins.clear();

	nlohmann::json j = nlohmann::json::parse(file);

	for (auto it = j.begin(); it != j.end(); ++it)
	{
		int index = std::stoi(it.key());
		if (index == -1)
			continue;

		const auto& vecAttributes = it.value();

		for (auto it2 = vecAttributes.begin(); it2 != vecAttributes.end(); ++it2)
		{
			int attributeIndex = std::stoi(it2.key());
			float attributeValue = it2.value();

			m_Skins[index].m_Attributes.push_back({ static_cast<uint16_t>(attributeIndex), attributeValue });
		}
	}

	file.close();
}