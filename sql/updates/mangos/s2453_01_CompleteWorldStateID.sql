-- https://wow.tools/dbc/?dbc=dungeonencounter&build=9.0.5.37774#page=1
ALTER TABLE `instance_dungeon_encounters` ADD COLUMN `CompleteWorldStateID` INT(11) NOT NULL DEFAULT '0' COMMENT 'Backported from later version - to be commented';

-- CompleteWorldStateID	ID	Name_lang
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4625 WHERE `Id` = 227; -- High Interrogator Gerstahn
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4626 WHERE `Id` = 228; -- Lord Roccor
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4627 WHERE `Id` = 229; -- Houndmaster Grebmar
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4628 WHERE `Id` = 230; -- Ring of Law
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4629 WHERE `Id` = 231; -- Pyromancer Loregrain
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4630 WHERE `Id` = 232; -- Lord Incendius
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4633 WHERE `Id` = 233; -- Warder Stilgiss
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4634 WHERE `Id` = 234; -- Fineous Darkvire
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4635 WHERE `Id` = 235; -- Bael'Gar
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4636 WHERE `Id` = 236; -- General Angerforge
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4637 WHERE `Id` = 237; -- Golem Lord Argelmach
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4638 WHERE `Id` = 238; -- Hurley Blackbreath
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4639 WHERE `Id` = 239; -- Phalanx
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4640 WHERE `Id` = 240; -- Ribbly Screwspigot
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4641 WHERE `Id` = 241; -- Plugger Spazzring
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4642 WHERE `Id` = 242; -- Ambassador Flamelash
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4643 WHERE `Id` = 243; -- The Seven
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4644 WHERE `Id` = 244; -- Magmus
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4645 WHERE `Id` = 245; -- Emperor Dagran Thaurissan
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4607 WHERE `Id` = 250; -- Yor
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4646 WHERE `Id` = 267; -- Highlord Omokk
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4647 WHERE `Id` = 268; -- Shadow Hunter Vosh'gajin
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4648 WHERE `Id` = 269; -- War Master Voone
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4649 WHERE `Id` = 270; -- Mother Smolderweb
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4650 WHERE `Id` = 271; -- Urok Doomhowl
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4651 WHERE `Id` = 272; -- Quartermaster Zigris
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4652 WHERE `Id` = 273; -- Gizrul the Slavener
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4653 WHERE `Id` = 274; -- Halycon
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4654 WHERE `Id` = 275; -- Overlord Wyrmthalak
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4669 WHERE `Id` = 343; -- Zevrim Thornhoof
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4670 WHERE `Id` = 344; -- Hydrospawn
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4671 WHERE `Id` = 345; -- Lethtendris
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4672 WHERE `Id` = 346; -- Alzzin the Wildshaper
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4676 WHERE `Id` = 347; -- Illyanna Ravenoak
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4675 WHERE `Id` = 348; -- Magister Kalendris
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4676 WHERE `Id` = 349; -- Immol'thar
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4673 WHERE `Id` = 350; -- Tendris Warpwood
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4677 WHERE `Id` = 361; -- Prince Tortheldrin
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4678 WHERE `Id` = 362; -- Guard Mol'dar
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4679 WHERE `Id` = 363; -- Stomper Kreeg
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4680 WHERE `Id` = 364; -- Guard Fengus
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4681 WHERE `Id` = 365; -- Guard Slip'kik
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4682 WHERE `Id` = 366; -- Captain Kromcrush
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4683 WHERE `Id` = 367; -- Cho'Rush the Observer
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 1544 WHERE `Id` = 368; -- King Gordok
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4693 WHERE `Id` = 378; -- Viscous Fallout
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4694 WHERE `Id` = 379; -- Grubbis
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4695 WHERE `Id` = 380; -- Electrocutioner 6000
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4696 WHERE `Id` = 381; -- Crowd Pummeler 9-60
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4697 WHERE `Id` = 382; -- Mekgineer Thermaplugg
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4703 WHERE `Id` = 422; -- Noxxion
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4704 WHERE `Id` = 423; -- Razorlash
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4705 WHERE `Id` = 424; -- Lord Vyletongue
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4706 WHERE `Id` = 425; -- Celebras the Cursed
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4707 WHERE `Id` = 426; -- Landslide
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4708 WHERE `Id` = 427; -- Tinkerer Gizlock
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4709 WHERE `Id` = 428; -- Rotgrip
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4710 WHERE `Id` = 429; -- Princess Theradras
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8591 WHERE `Id` = 438; -- Roogug
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4567 WHERE `Id` = 444; -- Interrogator Vishas
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4569 WHERE `Id` = 446; -- Houndmaster Loksey
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4570 WHERE `Id` = 447; -- Arcanist Doan
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4571 WHERE `Id` = 448; -- Herod
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4572 WHERE `Id` = 449; -- High Inquisitor Fairbanks
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 1201 WHERE `Id` = 450; -- High Inquisitor Whitemane
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4573 WHERE `Id` = 451; -- Kirtonos the Herald
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4574 WHERE `Id` = 452; -- Jandice Barov
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4575 WHERE `Id` = 453; -- Rattlegore
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4576 WHERE `Id` = 454; -- Marduk Blackpool
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4577 WHERE `Id` = 455; -- Vectus
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4578 WHERE `Id` = 456; -- Ras Frostwhisper
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4588 WHERE `Id` = 457; -- Instructor Malicia
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4589 WHERE `Id` = 458; -- Doctor Theolen Krastinov
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4590 WHERE `Id` = 459; -- Lorekeeper Polkelt
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4591 WHERE `Id` = 460; -- The Ravenian
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4592 WHERE `Id` = 461; -- Lord Alexei Barov
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4593 WHERE `Id` = 462; -- Lady Illucia Barov
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4594 WHERE `Id` = 463; -- Darkmaster Gandling
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4719 WHERE `Id` = 472; -- The Unforgiven
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4720 WHERE `Id` = 473; -- Hearthsinger Forresten
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4721 WHERE `Id` = 474; -- Timmy the Cruel
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4723 WHERE `Id` = 475; -- Willey Hopebreaker
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4722 WHERE `Id` = 476; -- Commander Malor
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4724 WHERE `Id` = 477; -- Instructor Galford
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4725 WHERE `Id` = 478; -- Balnazzar
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4726 WHERE `Id` = 479; -- Baroness Anastari
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4727 WHERE `Id` = 480; -- Nerub'enkan
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4728 WHERE `Id` = 481; -- Maleki the Pallid
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4729 WHERE `Id` = 482; -- Magistrate Barthilas
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4730 WHERE `Id` = 483; -- Ramstein the Gorger
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4731 WHERE `Id` = 484; -- Lord Aurius Rivendare
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4734 WHERE `Id` = 486; -- Dreamscythe
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4735 WHERE `Id` = 487; -- Weaver
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 121 WHERE `Id` = 488; -- Jammal'an the Prophet
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4737 WHERE `Id` = 490; -- Morphaz
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4738 WHERE `Id` = 491; -- Hazzas
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4739 WHERE `Id` = 492; -- Avatar of Hakkar
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4740 WHERE `Id` = 493; -- Shade of Eranikus
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3685 WHERE `Id` = 519; -- Frozen Commander
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3691 WHERE `Id` = 520; -- Grand Magus Telestra
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3691 WHERE `Id` = 521; -- Grand Magus Telestra
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3692 WHERE `Id` = 522; -- Anomalus
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3692 WHERE `Id` = 523; -- Anomalus
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3693 WHERE `Id` = 524; -- Ormorok the Tree-Shaper
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3693 WHERE `Id` = 525; -- Ormorok the Tree-Shaper
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3694 WHERE `Id` = 526; -- Keristrasza
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3694 WHERE `Id` = 527; -- Keristrasza
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3869 WHERE `Id` = 528; -- Drakos the Interrogator
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3869 WHERE `Id` = 529; -- Drakos the Interrogator
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3871 WHERE `Id` = 530; -- Varos Cloudstrider
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3871 WHERE `Id` = 531; -- Varos Cloudstrider
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3872 WHERE `Id` = 532; -- Mage-Lord Urom
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3872 WHERE `Id` = 533; -- Mage-Lord Urom
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3873 WHERE `Id` = 534; -- Ley-Guardian Eregos
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3873 WHERE `Id` = 535; -- Ley-Guardian Eregos
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4758 WHERE `Id` = 547; -- Revelosh
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4761 WHERE `Id` = 548; -- The Lost Dwarves
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4762 WHERE `Id` = 549; -- Ironaya
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4764 WHERE `Id` = 551; -- Ancient Stone Keeper
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4765 WHERE `Id` = 552; -- Galgann Firehammer
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4766 WHERE `Id` = 553; -- Grimlok
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4767 WHERE `Id` = 554; -- Archaedas
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4776 WHERE `Id` = 585; -- Lady Anacondra
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4777 WHERE `Id` = 586; -- Lord Cobrahn
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4778 WHERE `Id` = 587; -- Kresh
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4779 WHERE `Id` = 588; -- Lord Pythas
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4780 WHERE `Id` = 589; -- Skum
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4781 WHERE `Id` = 590; -- Lord Serpentis
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4782 WHERE `Id` = 591; -- Verdan the Everliving
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4783 WHERE `Id` = 592; -- Mutanus the Devourer
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4784 WHERE `Id` = 593; -- Hydromancer Velratha
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4785 WHERE `Id` = 594; -- Ghaz'rilla
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4786 WHERE `Id` = 595; -- Antu'sul
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4787 WHERE `Id` = 596; -- Theka the Martyr
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4788 WHERE `Id` = 597; -- Witch Doctor Zum'rah
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4789 WHERE `Id` = 598; -- Nekrum Gutchewer
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4790 WHERE `Id` = 599; -- Shadowpriest Sezz'ziz
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4791 WHERE `Id` = 600; -- Chief Ukorz Sandscalp
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3013 WHERE `Id` = 601; -- High Warlord Naj'entus
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3012 WHERE `Id` = 602; -- Supremus
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3058 WHERE `Id` = 603; -- Shade of Akama
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4792 WHERE `Id` = 604; -- Teron Gorefiend
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3014 WHERE `Id` = 605; -- Gurtogg Bloodboil
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4793 WHERE `Id` = 606; -- Reliquary of Souls
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 12150 WHERE `Id` = 607; -- Mother Shahraz
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3030 WHERE `Id` = 608; -- The Illidari Council
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4794 WHERE `Id` = 609; -- Illidan Stormrage
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4795 WHERE `Id` = 610; -- Razorgore the Untamed
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4796 WHERE `Id` = 611; -- Vaelastrasz the Corrupt
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4797 WHERE `Id` = 612; -- Broodlord Lashlayer
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4798 WHERE `Id` = 613; -- Firemaw
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4799 WHERE `Id` = 614; -- Ebonroc
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4800 WHERE `Id` = 615; -- Flamegor
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4801 WHERE `Id` = 616; -- Chromaggus
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 1641 WHERE `Id` = 617; -- Nefarian
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 2519 WHERE `Id` = 618; -- Rage Winterchill
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 2464 WHERE `Id` = 619; -- Anetheron
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 2523 WHERE `Id` = 620; -- Kaz'rogal
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 2487 WHERE `Id` = 621; -- Azgalor
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 2530 WHERE `Id` = 622; -- Archimonde
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 2853 WHERE `Id` = 623; -- Hydross the Unstable
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 2855 WHERE `Id` = 624; -- The Lurker Below
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 2857 WHERE `Id` = 625; -- Leotheras the Blind
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 2856 WHERE `Id` = 626; -- Fathom-Lord Karathress
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 2854 WHERE `Id` = 627; -- Morogrim Tidewalker
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4802 WHERE `Id` = 628; -- Lady Vashj
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 2778 WHERE `Id` = 649; -- High King Maulgar
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4804 WHERE `Id` = 650; -- Gruul the Dragonkiller
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4805 WHERE `Id` = 651; -- Magtheridon
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 2315 WHERE `Id` = 652; -- Attumen the Huntsman
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 2309 WHERE `Id` = 653; -- Moroes
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4806 WHERE `Id` = 654; -- Maiden of Virtue
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 2381 WHERE `Id` = 655; -- Opera Hall
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 2501 WHERE `Id` = 656; -- The Curator
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 2336 WHERE `Id` = 657; -- Terestian Illhoof
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 2910 WHERE `Id` = 658; -- Shade of Aran
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 2865 WHERE `Id` = 659; -- Netherspite
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 2517 WHERE `Id` = 660; -- Chess Event
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4807 WHERE `Id` = 661; -- Prince Malchezaar
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4808 WHERE `Id` = 662; -- Nightbane
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4809 WHERE `Id` = 663; -- Lucifron
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 847 WHERE `Id` = 664; -- Magmadar
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 848 WHERE `Id` = 665; -- Gehennas
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 846 WHERE `Id` = 666; -- Garr
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 850 WHERE `Id` = 667; -- Shazzrah
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 845 WHERE `Id` = 668; -- Baron Geddon
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 761 WHERE `Id` = 669; -- Sulfuron Harbinger
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 741 WHERE `Id` = 670; -- Golemagg the Incinerator
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 1502 WHERE `Id` = 671; -- Majordomo Executus
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 1666 WHERE `Id` = 672; -- Ragnaros
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4821 WHERE `Id` = 709; -- The Prophet Skeram
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4822 WHERE `Id` = 710; -- Silithid Royalty
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4823 WHERE `Id` = 711; -- Battleguard Sartura
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4824 WHERE `Id` = 712; -- Fankriss the Unyielding
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4825 WHERE `Id` = 713; -- Viscidus
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4826 WHERE `Id` = 714; -- Princess Huhuran
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4827 WHERE `Id` = 715; -- Twin Emperors
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 2296 WHERE `Id` = 716; -- Ouro
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4828 WHERE `Id` = 717; -- C'Thun
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4811 WHERE `Id` = 718; -- Kurinnaxx
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 2174 WHERE `Id` = 719; -- General Rajaxx
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4812 WHERE `Id` = 720; -- Moam
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4813 WHERE `Id` = 721; -- Buru the Gorger
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4814 WHERE `Id` = 722; -- Ayamiss the Hunter
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4815 WHERE `Id` = 723; -- Ossirian the Unscarred
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3434 WHERE `Id` = 724; -- Kalecgos
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3336 WHERE `Id` = 725; -- Brutallus
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3337 WHERE `Id` = 726; -- Felmyst
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3435 WHERE `Id` = 727; -- Eredar Twins
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3423 WHERE `Id` = 728; -- M'uru
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4816 WHERE `Id` = 729; -- Kil'jaeden
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4817 WHERE `Id` = 730; -- Al'ar
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4818 WHERE `Id` = 731; -- Void Reaver
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4819 WHERE `Id` = 732; -- High Astromancer Solarian
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4820 WHERE `Id` = 733; -- Kael'thas Sunstrider
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 1967 WHERE `Id` = 784; -- High Priest Venoxis
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 1968 WHERE `Id` = 785; -- High Priestess Jeklik
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 1969 WHERE `Id` = 786; -- High Priestess Mar'li
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4839 WHERE `Id` = 787; -- Bloodlord Mandokir
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4850 WHERE `Id` = 788; -- Edge of Madness
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 1970 WHERE `Id` = 789; -- High Priest Thekal
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4840 WHERE `Id` = 790; -- Gahz'ranka
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 1971 WHERE `Id` = 791; -- High Priestess Arlokk
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4841 WHERE `Id` = 792; -- Jin'do the Hexxer
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4844 WHERE `Id` = 793; -- Hakkar
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5182 WHERE `Id` = 1022; -- Atramedes
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5318 WHERE `Id` = 1023; -- Chimaeron
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5301 WHERE `Id` = 1024; -- Magmaw
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5315 WHERE `Id` = 1025; -- Maloriak
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5203 WHERE `Id` = 1026; -- Nefarian's End
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5303 WHERE `Id` = 1027; -- Omnotron Defense System
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5339 WHERE `Id` = 1028; -- Ascendant Council
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5494 WHERE `Id` = 1029; -- Cho'gall
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5380 WHERE `Id` = 1030; -- Halfus Wyrmbreaker
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5517 WHERE `Id` = 1032; -- Theralion and Valiona
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5575 WHERE `Id` = 1033; -- Argaloth
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5565 WHERE `Id` = 1034; -- Al'Akir
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5563 WHERE `Id` = 1035; -- Conclave of Wind
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5131 WHERE `Id` = 1036; -- Ascendant Lord Obsidius
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5129 WHERE `Id` = 1037; -- Beauty
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5112 WHERE `Id` = 1038; -- Corla, Herald of Twilight
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5119 WHERE `Id` = 1039; -- Karsh Steelbender
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5127 WHERE `Id` = 1040; -- Rom'ogg Bonecrusher
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5497 WHERE `Id` = 1041; -- Altairus
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5496 WHERE `Id` = 1042; -- Asaad
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5500 WHERE `Id` = 1043; -- Grand Vizier Ertan
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5325 WHERE `Id` = 1044; -- Commander Ulthok
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5125 WHERE `Id` = 1045; -- Lady Naz'jar
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5326 WHERE `Id` = 1046; -- Mindbender Ghur'sha
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5557 WHERE `Id` = 1047; -- Ozumat
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5098 WHERE `Id` = 1048; -- Drahga Shadowburner
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5175 WHERE `Id` = 1049; -- Erudax
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5077 WHERE `Id` = 1050; -- Forgemaster Throngus
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5065 WHERE `Id` = 1051; -- General Umbriss
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5389 WHERE `Id` = 1052; -- General Husam
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5382 WHERE `Id` = 1053; -- High Prophet Barim
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5562 WHERE `Id` = 1054; -- Lockmaw
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5476 WHERE `Id` = 1055; -- Siamat
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5569 WHERE `Id` = 1056; -- Corborus
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5572 WHERE `Id` = 1057; -- High Priestess Azil
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5571 WHERE `Id` = 1058; -- Ozruk
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5570 WHERE `Id` = 1059; -- Slabhide
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5556 WHERE `Id` = 1060; -- "Captain" Cookie
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5555 WHERE `Id` = 1062; -- Admiral Ripsnarl
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5554 WHERE `Id` = 1063; -- Foe Reaper 5000
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5538 WHERE `Id` = 1064; -- Glubtok
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5549 WHERE `Id` = 1065; -- Helix Gearbreaker
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5551 WHERE `Id` = 1069; -- Baron Ashbury
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4597 WHERE `Id` = 1070; -- Baron Silverlaine
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4598 WHERE `Id` = 1071; -- Commander Springvale
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5553 WHERE `Id` = 1072; -- Lord Godfrey
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5552 WHERE `Id` = 1073; -- Lord Walden
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5166 WHERE `Id` = 1074; -- Ammunae
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5107 WHERE `Id` = 1075; -- Anraphet
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5165 WHERE `Id` = 1076; -- Earthrager Ptah
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5002 WHERE `Id` = 1077; -- Isiset
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5168 WHERE `Id` = 1078; -- Rajh
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5167 WHERE `Id` = 1079; -- Setesh
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4985 WHERE `Id` = 1080; -- Temple Guardian Anhuur
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5613 WHERE `Id` = 1081; -- Vanessa VanCleef
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5523 WHERE `Id` = 1082; -- Sinestra
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5523 WHERE `Id` = 1083; -- Sinestra
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4810 WHERE `Id` = 1084; -- Onyxia
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4241 WHERE `Id` = 1085; -- Anub'arak
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4803 WHERE `Id` = 1086; -- Faction Champions
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4272 WHERE `Id` = 1087; -- Lord Jaraxxus
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4370 WHERE `Id` = 1088; -- Northrend Beasts
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4334 WHERE `Id` = 1089; -- Val'kyr Twins
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4833 WHERE `Id` = 1090; -- Sartharion
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4831 WHERE `Id` = 1091; -- Shadron
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4830 WHERE `Id` = 1092; -- Tenebron
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4832 WHERE `Id` = 1093; -- Vesperon
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4829 WHERE `Id` = 1094; -- Malygos
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4733 WHERE `Id` = 1095; -- Blood Council
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4519 WHERE `Id` = 1096; -- Deathbringer Saurfang
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4870 WHERE `Id` = 1097; -- Festergut
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4855 WHERE `Id` = 1098; -- Valithria Dreamwalker
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4492 WHERE `Id` = 1099; -- Icecrown Gunship Battle
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4869 WHERE `Id` = 1100; -- Lady Deathwhisper
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4471 WHERE `Id` = 1101; -- Lord Marrowgar
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4871 WHERE `Id` = 1102; -- Professor Putricide
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4868 WHERE `Id` = 1103; -- Queen Lana'thel
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4435 WHERE `Id` = 1104; -- Rotface
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4842 WHERE `Id` = 1105; -- Sindragosa
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4910 WHERE `Id` = 1106; -- The Lich King
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 2255 WHERE `Id` = 1107; -- Anub'Rekhan
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 2242 WHERE `Id` = 1108; -- Gluth
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 2238 WHERE `Id` = 1109; -- Gothik the Harvester
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 2256 WHERE `Id` = 1110; -- Grand Widow Faerlina
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 2247 WHERE `Id` = 1111; -- Grobbulus
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 2258 WHERE `Id` = 1112; -- Heigan the Unclean
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 2307 WHERE `Id` = 1113; -- Instructor Razuvious
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 2269 WHERE `Id` = 1114; -- Kel'Thuzad
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 2245 WHERE `Id` = 1115; -- Loatheb
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 2253 WHERE `Id` = 1116; -- Maexxna
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 2257 WHERE `Id` = 1117; -- Noth the Plaguebringer
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 2244 WHERE `Id` = 1118; -- Patchwerk
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 2268 WHERE `Id` = 1119; -- Sapphiron
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 2243 WHERE `Id` = 1120; -- Thaddius
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4012 WHERE `Id` = 1121; -- The Four Horsemen
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4836 WHERE `Id` = 1126; -- Archavon the Stone Watcher
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4837 WHERE `Id` = 1127; -- Emalon the Storm Watcher
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4838 WHERE `Id` = 1128; -- Koralon the Flame Watcher
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4895 WHERE `Id` = 1129; -- Toravon the Ice Watcher
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4093 WHERE `Id` = 1130; -- Algalon the Observer
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4140 WHERE `Id` = 1131; -- Auriaya
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4114 WHERE `Id` = 1132; -- Flame Leviathan
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4059 WHERE `Id` = 1133; -- Freya
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4067 WHERE `Id` = 1134; -- General Vezax
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4050 WHERE `Id` = 1135; -- Hodir
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4834 WHERE `Id` = 1136; -- Ignis the Furnace Master
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4089 WHERE `Id` = 1137; -- Kologarn
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4060 WHERE `Id` = 1138; -- Mimiron
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4835 WHERE `Id` = 1139; -- Razorscale
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4091 WHERE `Id` = 1140; -- The Assembly of Iron
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4057 WHERE `Id` = 1141; -- Thorim
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4138 WHERE `Id` = 1142; -- XT-002 Deconstructor
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4121 WHERE `Id` = 1143; -- Yogg-Saron
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5509 WHERE `Id` = 1144; -- Hogger
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5510 WHERE `Id` = 1145; -- Lord Overheat
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5511 WHERE `Id` = 1146; -- Randolph Moloch
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5031 WHERE `Id` = 1147; -- Baltharus the Warborn
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5033 WHERE `Id` = 1148; -- General Zarithrian
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5032 WHERE `Id` = 1149; -- Saviana Ragefire
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5048 WHERE `Id` = 1150; -- Halion
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5630 WHERE `Id` = 1164; -- Elder Brightleaf
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5631 WHERE `Id` = 1165; -- Elder Ironbranch
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5632 WHERE `Id` = 1166; -- Elder Stonebark
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5779 WHERE `Id` = 1178; -- High Priest Venoxis
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5810 WHERE `Id` = 1179; -- Bloodlord Mandokir
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5780 WHERE `Id` = 1180; -- High Priestess Kilnara
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5769 WHERE `Id` = 1181; -- Zanzil
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5778 WHERE `Id` = 1182; -- Jin'do the Godbreaker
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5827 WHERE `Id` = 1185; -- Majordomo Staghelm
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5824 WHERE `Id` = 1188; -- Cache of Madness
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3122 WHERE `Id` = 1189; -- Akil'zon
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3077 WHERE `Id` = 1190; -- Nalorakk
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3153 WHERE `Id` = 1191; -- Jan'alai
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3152 WHERE `Id` = 1192; -- Halazzi
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3146 WHERE `Id` = 1193; -- Hex Lord Malacrass
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3148 WHERE `Id` = 1194; -- Daakara
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5882 WHERE `Id` = 1197; -- Beth'tilac
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5898 WHERE `Id` = 1200; -- Baleroc
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5911 WHERE `Id` = 1203; -- Ragnaros
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5872 WHERE `Id` = 1204; -- Lord Rhyolith
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5919 WHERE `Id` = 1205; -- Shannox
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5942 WHERE `Id` = 1206; -- Alysrazor
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 5821 WHERE `Id` = 1250; -- Occu'thar
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6048 WHERE `Id` = 1271; -- Murozond
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6067 WHERE `Id` = 1272; -- Peroth'arn
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6038 WHERE `Id` = 1273; -- Queen Azshara
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6055 WHERE `Id` = 1274; -- Mannoroth
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6097 WHERE `Id` = 1291; -- Spine of Deathwing
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6082 WHERE `Id` = 1292; -- Morchok
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6084 WHERE `Id` = 1294; -- Warlord Zon'ozz
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6102 WHERE `Id` = 1295; -- Yor'sahj the Unsleeping
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6106 WHERE `Id` = 1296; -- Hagara
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6128 WHERE `Id` = 1297; -- Ultraxion
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6134 WHERE `Id` = 1298; -- Warmaster Blackhorn
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6142 WHERE `Id` = 1299; -- Madness of Deathwing
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6585 WHERE `Id` = 1303; -- Gu Cloudstrike
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6117 WHERE `Id` = 1304; -- Master Snowdrift
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6138 WHERE `Id` = 1305; -- Sha of Violence
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6151 WHERE `Id` = 1306; -- Taran Zhu
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6158 WHERE `Id` = 1332; -- Alizabal
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6161 WHERE `Id` = 1337; -- Arcurion
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6088 WHERE `Id` = 1339; -- Archbishop Benedictus
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6062 WHERE `Id` = 1340; -- Asira Dawnslayer
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6215 WHERE `Id` = 1348; -- Omar the Test Dragon
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6428 WHERE `Id` = 1390; -- Feng the Accursed
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6431 WHERE `Id` = 1395; -- The Stone Guard
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6153 WHERE `Id` = 1397; -- Saboteur Kip'tilak
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6465 WHERE `Id` = 1405; -- Striker Ga'dok
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6466 WHERE `Id` = 1406; -- Commander Ri'mok
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6470 WHERE `Id` = 1407; -- Will of the Emperor
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6473 WHERE `Id` = 1409; -- Protectors of the Endless
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6143 WHERE `Id` = 1412; -- Ook-Ook
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6375 WHERE `Id` = 1413; -- Hoptallus
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6378 WHERE `Id` = 1414; -- Yan-Zhu the Uncasked
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6141 WHERE `Id` = 1416; -- Liu Flameheart
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6295 WHERE `Id` = 1417; -- Lorewalker Stonestep
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6400 WHERE `Id` = 1418; -- Wise Mari
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6293 WHERE `Id` = 1419; -- Raigonn
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6330 WHERE `Id` = 1420; -- Flameweaver Koegler
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6542 WHERE `Id` = 1421; -- Armsmaster Harlan
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6521 WHERE `Id` = 1422; -- Houndmaster Braun
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4568 WHERE `Id` = 1423; -- Thalnos the Soulrender
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6444 WHERE `Id` = 1424; -- Brother Korloff
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6450 WHERE `Id` = 1425; -- High Inquisitor Whitemane
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6321 WHERE `Id` = 1426; -- Instructor Chillheart
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6331 WHERE `Id` = 1427; -- Jandice Barov
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6335 WHERE `Id` = 1428; -- Rattlegore
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6334 WHERE `Id` = 1429; -- Lilian Voss
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6319 WHERE `Id` = 1430; -- Darkmaster Gandling
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6525 WHERE `Id` = 1431; -- Sha of Fear
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6463 WHERE `Id` = 1434; -- Gara'jal the Spiritbinder
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6529 WHERE `Id` = 1436; -- The Spirit Kings
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6125 WHERE `Id` = 1439; -- Sha of Doubt
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6579 WHERE `Id` = 1441; -- Xin the Weaponmaster
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6586 WHERE `Id` = 1442; -- Trial of the King
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6580 WHERE `Id` = 1443; -- Adarogg
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6583 WHERE `Id` = 1444; -- Dark Shaman Koranthal
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6589 WHERE `Id` = 1445; -- Slagmaw
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6592 WHERE `Id` = 1446; -- Lava Guard Gordoth
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6594 WHERE `Id` = 1447; -- General Pa'valak
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6649 WHERE `Id` = 1463; -- Garalon
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6658 WHERE `Id` = 1464; -- Wing Leader Ner'onok
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6625 WHERE `Id` = 1465; -- Vizier Jin'bak
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6677 WHERE `Id` = 1498; -- Wind Lord Mel'jarak
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6700 WHERE `Id` = 1499; -- Amber-Shaper Un'sok
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6786 WHERE `Id` = 1500; -- Elegon
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6729 WHERE `Id` = 1501; -- Grand Empress Shek'zeer
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6735 WHERE `Id` = 1502; -- Commander Vo'jak
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6944 WHERE `Id` = 1504; -- Blade Lord Ta'yak
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6747 WHERE `Id` = 1505; -- Tsulong
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6738 WHERE `Id` = 1506; -- Lei Shi
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6741 WHERE `Id` = 1507; -- Imperial Vizier Zor'lok
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6558 WHERE `Id` = 1509; -- Gekkan
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6558 WHERE `Id` = 1510; -- Gekkan
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 7329 WHERE `Id` = 1559; -- Iron Qon
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 7502 WHERE `Id` = 1560; -- Twin Consorts
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 0 WHERE `Id` = 1563; -- Galleon
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 0 WHERE `Id` = 1564; -- Sha of Anger
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 7507 WHERE `Id` = 1565; -- Tortos
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 7543 WHERE `Id` = 1570; -- Council of Elders
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 0 WHERE `Id` = 1571; -- Nalak
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 7563 WHERE `Id` = 1572; -- Durumu the Forgotten
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 7565 WHERE `Id` = 1573; -- Ji-Kun
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 7571 WHERE `Id` = 1574; -- Primordius
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 7570 WHERE `Id` = 1575; -- Horridon
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 7582 WHERE `Id` = 1576; -- Dark Animus
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 7575 WHERE `Id` = 1577; -- Jin'rokh the Breaker
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 7577 WHERE `Id` = 1578; -- Megaera
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 7603 WHERE `Id` = 1579; -- Lei Shen
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 7605 WHERE `Id` = 1580; -- Ra-den
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 7605 WHERE `Id` = 1581; -- Ra-den
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 0 WHERE `Id` = 1587; -- Oondasta
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8109 WHERE `Id` = 1593; -- Paragons of the Klaxxi
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8202 WHERE `Id` = 1594; -- Spoils of Pandaria
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8225 WHERE `Id` = 1595; -- Malkorok
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8253 WHERE `Id` = 1598; -- Fallen Protectors
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8258 WHERE `Id` = 1599; -- Thok the Bloodthirsty
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8260 WHERE `Id` = 1600; -- Iron Juggernaut
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8236 WHERE `Id` = 1601; -- Siegecrafter Blackfuse
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8268 WHERE `Id` = 1602; -- Immerseus
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8272 WHERE `Id` = 1603; -- General Nazgrim
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8276 WHERE `Id` = 1604; -- Sha of Pride
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6215 WHERE `Id` = 1605; -- Omar's Test Encounter (Cosmetic only) DNT
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8285 WHERE `Id` = 1606; -- Kor'kron Dark Shaman
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8415 WHERE `Id` = 1622; -- Galakras
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8356 WHERE `Id` = 1623; -- Garrosh Hellscream
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8299 WHERE `Id` = 1624; -- Norushen
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8565 WHERE `Id` = 1652; -- Roltall
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8563 WHERE `Id` = 1653; -- Slave Watcher Crushto
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8566 WHERE `Id` = 1654; -- Gug'rokk
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8586 WHERE `Id` = 1655; -- Magmolatus
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8592 WHERE `Id` = 1656; -- Hunter Bonetusk
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8595 WHERE `Id` = 1659; -- Warlord Ramtusk
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8620 WHERE `Id` = 1660; -- Groyat, the Blind Hunter
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8597 WHERE `Id` = 1661; -- Charlga Razorflank
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8622 WHERE `Id` = 1662; -- Aaurx
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8623 WHERE `Id` = 1663; -- Mordresh Fire Eye
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8624 WHERE `Id` = 1664; -- Mushlump
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8625 WHERE `Id` = 1665; -- Death Speaker Blackthorn
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8626 WHERE `Id` = 1666; -- Amnennar the Coldbringer
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4617 WHERE `Id` = 1667; -- Ghamoo-ra
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8615 WHERE `Id` = 1668; -- Domina
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8614 WHERE `Id` = 1669; -- Subjugator Kor'ul
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4623 WHERE `Id` = 1670; -- Executioner Gore
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4623 WHERE `Id` = 1671; -- Twilight Lord Bathiel
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4624 WHERE `Id` = 1672; -- Aku'mai
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8653 WHERE `Id` = 1675; -- Thruk
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8655 WHERE `Id` = 1676; -- Guardian of the Deep
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8661 WHERE `Id` = 1677; -- Sadana Bloodfury
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8665 WHERE `Id` = 1678; -- Azzakel, Vanguard of the Legion
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8678 WHERE `Id` = 1679; -- Bonemaw
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8691 WHERE `Id` = 1682; -- Ner'zhul
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8667 WHERE `Id` = 1685; -- Soulbinder Nyami
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8669 WHERE `Id` = 1686; -- Vigilant Kaathar
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8705 WHERE `Id` = 1688; -- Nhallish
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8720 WHERE `Id` = 1689; -- Flamebender Ka'graz
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8724 WHERE `Id` = 1690; -- Blast Furnace
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8731 WHERE `Id` = 1691; -- Gruul
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8733 WHERE `Id` = 1692; -- Operator Thogar
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8738 WHERE `Id` = 1693; -- Hans'gar & Franzok
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8746 WHERE `Id` = 1694; -- Beastlord Darmac
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8755 WHERE `Id` = 1695; -- The Iron Maidens
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8761 WHERE `Id` = 1696; -- Oregorger the Devourer
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8770 WHERE `Id` = 1698; -- Ranjit
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8771 WHERE `Id` = 1699; -- Araknath
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8772 WHERE `Id` = 1700; -- Rukhran
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8773 WHERE `Id` = 1701; -- High Sage Viryx
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8874 WHERE `Id` = 1704; -- Blackhand
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8800 WHERE `Id` = 1705; -- Imperator Mar'gok
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8806 WHERE `Id` = 1706; -- The Butcher
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8831 WHERE `Id` = 1713; -- Kromog, Legend of the Mountain
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8843 WHERE `Id` = 1714; -- Teron'gor
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8848 WHERE `Id` = 1715; -- Rocketspark and Borka
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8866 WHERE `Id` = 1719; -- Twin Ogron
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8884 WHERE `Id` = 1720; -- Brackenspore
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8903 WHERE `Id` = 1721; -- Kargath Bladefist
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8923 WHERE `Id` = 1722; -- Tectus, The Living Mountain
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8930 WHERE `Id` = 1723; -- Ko'ragh
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8948 WHERE `Id` = 1732; -- Nitrogg Thundertower
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 9038 WHERE `Id` = 1736; -- Skylord Tovra
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 0 WHERE `Id` = 1745; -- Ashran
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 9175 WHERE `Id` = 1746; -- Witherbark
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 0 WHERE `Id` = 1747; -- Ken's Test Encounter [DNT]
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 9219 WHERE `Id` = 1748; -- Grimrail Enforcers
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 9233 WHERE `Id` = 1749; -- Fleshrender Nok'gar
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 9235 WHERE `Id` = 1750; -- Oshir
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 9297 WHERE `Id` = 1751; -- Archmage Sol
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 9298 WHERE `Id` = 1752; -- Xeri'tac
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 9341 WHERE `Id` = 1754; -- Skulloc, Son of Gruul
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 0 WHERE `Id` = 1755; -- Rukhmar, Sun-God of the Arakkoa
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 9354 WHERE `Id` = 1756; -- Yalnu
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 9356 WHERE `Id` = 1757; -- Ancient Protectors
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 9020 WHERE `Id` = 1758; -- Kyrak
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 9060 WHERE `Id` = 1759; -- Commander Tharbek
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8703 WHERE `Id` = 1760; -- Ragewing the Untamed
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 8699 WHERE `Id` = 1761; -- Orebender Gor'ashan
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 9373 WHERE `Id` = 1762; -- Warlord Zaela
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 0 WHERE `Id` = 1770; -- Tarlna the Ageless
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10004 WHERE `Id` = 1777; -- Fel Lord Zakuun
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10010 WHERE `Id` = 1778; -- Hellfire Assault
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10039 WHERE `Id` = 1783; -- Gorefiend
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10041 WHERE `Id` = 1784; -- Tyrant Velhari
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10043 WHERE `Id` = 1785; -- Iron Reaver
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10048 WHERE `Id` = 1786; -- Kilrogg Deadeye
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10051 WHERE `Id` = 1787; -- Kormrok
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10060 WHERE `Id` = 1788; -- Shadow-Lord Iskar
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10092 WHERE `Id` = 1790; -- Rokmora
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10094 WHERE `Id` = 1791; -- Ularogg Cragshaper
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10097 WHERE `Id` = 1792; -- Naraxas
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10099 WHERE `Id` = 1793; -- Dargrul the Underking
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10101 WHERE `Id` = 1794; -- Socrethar the Eternal
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10141 WHERE `Id` = 1795; -- Mannoroth
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10177 WHERE `Id` = 1798; -- Hellfire High Council
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10179 WHERE `Id` = 1799; -- Archimonde
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10208 WHERE `Id` = 1800; -- Xhul'horac
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 0 WHERE `Id` = 1801; -- Supreme Lord Kazzak
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10335 WHERE `Id` = 1805; -- Hymdall
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10365 WHERE `Id` = 1806; -- Hyrja
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10367 WHERE `Id` = 1807; -- Fenryr
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10369 WHERE `Id` = 1808; -- God-King Skovald
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10371 WHERE `Id` = 1809; -- Odyn
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10382 WHERE `Id` = 1810; -- Warlord Parjesh
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10384 WHERE `Id` = 1811; -- Lady Hatecoil
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10388 WHERE `Id` = 1812; -- King Deepbeard
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10386 WHERE `Id` = 1813; -- Serpentrix
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10390 WHERE `Id` = 1814; -- Wrath of Azshara
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10392 WHERE `Id` = 1815; -- Tirathon Saltheril
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10397 WHERE `Id` = 1816; -- Ash'Golm
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10398 WHERE `Id` = 1817; -- Glazer
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10401 WHERE `Id` = 1818; -- Cordana Felsong
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10479 WHERE `Id` = 1822; -- Ymiron, the Fallen King
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10482 WHERE `Id` = 1823; -- Harbaron
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10484 WHERE `Id` = 1824; -- Helya
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10562 WHERE `Id` = 1825; -- Corstilax
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10566 WHERE `Id` = 1826; -- Nal'tira
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10563 WHERE `Id` = 1827; -- Ivanyr
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10564 WHERE `Id` = 1828; -- General Xakal
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10565 WHERE `Id` = 1829; -- Advisor Vandros
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10580 WHERE `Id` = 1832; -- Amalgam of Souls
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10582 WHERE `Id` = 1833; -- Ilysanna Ravencrest
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10584 WHERE `Id` = 1834; -- Smashspite the Hateful
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10586 WHERE `Id` = 1835; -- Lord Kur'talos Ravencrest
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10381 WHERE `Id` = 1836; -- Archdruid Glaidalis
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10592 WHERE `Id` = 1837; -- Oakheart
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10593 WHERE `Id` = 1838; -- Dresaron
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10594 WHERE `Id` = 1839; -- Shade of Xavius
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10640 WHERE `Id` = 1841; -- Ursoc
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10668 WHERE `Id` = 1842; -- Krosus
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10707 WHERE `Id` = 1845; -- Shivermaw
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10713 WHERE `Id` = 1846; -- Mindflayer Kaahrj
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10718 WHERE `Id` = 1847; -- Millificent Manastorm
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10721 WHERE `Id` = 1848; -- Festerface
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10728 WHERE `Id` = 1849; -- Skorpyron
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10730 WHERE `Id` = 1850; -- Inquisitor Tormentorum
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10737 WHERE `Id` = 1851; -- Sael'orn
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10742 WHERE `Id` = 1852; -- Anub'esset
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10758 WHERE `Id` = 1853; -- Nythendra
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10762 WHERE `Id` = 1854; -- Dragons of Nightmare
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10767 WHERE `Id` = 1855; -- Blood-Princess Thal'ena
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10771 WHERE `Id` = 1856; -- Fel Lord Betrug
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10906 WHERE `Id` = 1862; -- Tichondrius
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 11101 WHERE `Id` = 1863; -- Star Augur Etraeus
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10922 WHERE `Id` = 1864; -- Xavius
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 10953 WHERE `Id` = 1865; -- Chronomatic Anomaly
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 11037 WHERE `Id` = 1866; -- Gul'dan
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 11083 WHERE `Id` = 1867; -- Trilliax
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 11089 WHERE `Id` = 1868; -- Patrol Captain Gerdo
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 11091 WHERE `Id` = 1869; -- Talixae Flamewreath
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 11093 WHERE `Id` = 1870; -- Advisor Melandrus
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 11377 WHERE `Id` = 1871; -- Spellblade Aluriel
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 11442 WHERE `Id` = 1872; -- Grand Magistrix Elisande
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 11476 WHERE `Id` = 1873; -- Il'gynoth, The Heart of Corruption
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 0 WHERE `Id` = 1874; -- Raid Boss Dummy (5min)
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 0 WHERE `Id` = 1875; -- Raid Boss Dummy (10min)
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 11502 WHERE `Id` = 1876; -- Elerethe Renferal
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 11498 WHERE `Id` = 1877; -- Cenarius
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 0 WHERE `Id` = 1879; -- The Soultakers
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 0 WHERE `Id` = 1880; -- Nithogg
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6072 WHERE `Id` = 1881; -- Echo of Baine
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6072 WHERE `Id` = 1882; -- Echo of Sylvanas
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6073 WHERE `Id` = 1883; -- Echo of Jaina
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6073 WHERE `Id` = 1884; -- Echo of Tyrande
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4725 WHERE `Id` = 1885; -- Postmaster Malown
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 11887 WHERE `Id` = 1886; -- High Botanist Tel'arn
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4761 WHERE `Id` = 1887; -- Obsidian Sentinel
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 0 WHERE `Id` = 1888; -- Shar'thos
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 2702 WHERE `Id` = 1889; -- Exarch Maladaar
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4603 WHERE `Id` = 1890; -- Shirrak the Dead Watcher
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4699 WHERE `Id` = 1891; -- Omor the Unscarred
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4700 WHERE `Id` = 1892; -- Vazruden the Herald
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4698 WHERE `Id` = 1893; -- Watchkeeper Gargolmar
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4702 WHERE `Id` = 1894; -- Kael'thas Sunstrider
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3450 WHERE `Id` = 1895; -- Priestess Delrissa
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3448 WHERE `Id` = 1897; -- Selin Fireheart
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3449 WHERE `Id` = 1898; -- Vexallus
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4606 WHERE `Id` = 1899; -- Nexus-Prince Shaffar
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4604 WHERE `Id` = 1900; -- Pandemonius
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4605 WHERE `Id` = 1901; -- Tavarok
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 2818 WHERE `Id` = 1902; -- Talon King Ikiss
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4608 WHERE `Id` = 1903; -- Darkweaver Syth
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3022 WHERE `Id` = 1904; -- Anzu
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4659 WHERE `Id` = 1905; -- Lieutenant Drake
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4660 WHERE `Id` = 1906; -- Epoch Hunter
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 2711 WHERE `Id` = 1907; -- Captain Skarloc
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4609 WHERE `Id` = 1908; -- Ambassador Hellmaw
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 2802 WHERE `Id` = 1909; -- Blackheart the Inciter
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4610 WHERE `Id` = 1910; -- Murmur
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 2803 WHERE `Id` = 1911; -- Grandmaster Vorpil
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4742 WHERE `Id` = 1913; -- Dalliah the Doomsayer
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4744 WHERE `Id` = 1914; -- Harbinger Skyriss
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4743 WHERE `Id` = 1915; -- Wrath-Scryer Soccothrates
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4741 WHERE `Id` = 1916; -- Zereketh the Unbound
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 0 WHERE `Id` = 1917; -- Humongris
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 0 WHERE `Id` = 1918; -- Timed Damage Dummy
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 2819 WHERE `Id` = 1919; -- Aeonus
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 2820 WHERE `Id` = 1920; -- Chrono Lord Deja
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 2821 WHERE `Id` = 1921; -- Temporus
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 2400 WHERE `Id` = 1922; -- The Maker
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 2403 WHERE `Id` = 1923; -- Keli'dan the Breaker
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4854 WHERE `Id` = 1924; -- Broggok
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4745 WHERE `Id` = 1925; -- Commander Sarannis
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4746 WHERE `Id` = 1926; -- High Botanist Freywinn
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4748 WHERE `Id` = 1927; -- Laj
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4747 WHERE `Id` = 1928; -- Thorngrin the Tender
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4749 WHERE `Id` = 1929; -- Warp Splinter
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4751 WHERE `Id` = 1930; -- Nethermancer Sepethrea
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4752 WHERE `Id` = 1931; -- Pathaleon the Calculator
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4750 WHERE `Id` = 1932; -- Mechano-Lord Capacitus
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 12051 WHERE `Id` = 1933; -- Gatewatcher Gyro-Kill
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 12053 WHERE `Id` = 1934; -- Gatewatcher Iron-Hand
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4701 WHERE `Id` = 1935; -- Blood Guard Porung
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 2804 WHERE `Id` = 1936; -- Grand Warlock Nethekurse
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 2844 WHERE `Id` = 1937; -- Warbringer O'mrogg
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 2907 WHERE `Id` = 1938; -- Warchief Kargath Bladefist
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4661 WHERE `Id` = 1939; -- Mennu the Betrayer
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 2532 WHERE `Id` = 1940; -- Quagmirran
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4662 WHERE `Id` = 1941; -- Rokmar the Crackler
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4663 WHERE `Id` = 1942; -- Hydromancer Thespia
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4664 WHERE `Id` = 1943; -- Mekgineer Steamrigger
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4665 WHERE `Id` = 1944; -- Warlord Kalithresh
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4667 WHERE `Id` = 1945; -- Ghaz'an
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4666 WHERE `Id` = 1946; -- Hungarfen
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 2448 WHERE `Id` = 1947; -- Swamplord Musel'ek
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4668 WHERE `Id` = 1948; -- The Black Stalker
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 0 WHERE `Id` = 1949; -- Drugon the Frostblood
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 0 WHERE `Id` = 1950; -- Na'zak the Fiend
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 0 WHERE `Id` = 1951; -- Flotsam
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 0 WHERE `Id` = 1952; -- Calamir
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 0 WHERE `Id` = 1953; -- Levantus
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 12521 WHERE `Id` = 1954; -- Maiden of Virtue
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 12534 WHERE `Id` = 1957; -- Opera Hall
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 12546 WHERE `Id` = 1958; -- Odyn
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 12548 WHERE `Id` = 1959; -- Mana Devourer
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 12542 WHERE `Id` = 1960; -- Attumen the Huntsman
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 12554 WHERE `Id` = 1961; -- Moroes
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 12556 WHERE `Id` = 1962; -- Guarm
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 12560 WHERE `Id` = 1964; -- The Curator
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 12566 WHERE `Id` = 1965; -- Shade of Medivh
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3870 WHERE `Id` = 1966; -- Prince Taldaram
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4612 WHERE `Id` = 1967; -- Jedoga Shadowseeker
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4613 WHERE `Id` = 1968; -- Herald Volazj
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4611 WHERE `Id` = 1969; -- Elder Nadox
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3874 WHERE `Id` = 1971; -- Krik'thir the Gatewatcher
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4615 WHERE `Id` = 1972; -- Hadronox
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4616 WHERE `Id` = 1973; -- Anub'arak
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4684 WHERE `Id` = 1974; -- Trollgore
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4687 WHERE `Id` = 1975; -- The Prophet Tharon'ja
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4685 WHERE `Id` = 1976; -- Novos the Summoner
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4686 WHERE `Id` = 1977; -- King Dred
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3852 WHERE `Id` = 1978; -- Slad'ran
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3851 WHERE `Id` = 1980; -- Moorabi
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3850 WHERE `Id` = 1981; -- Gal'darah
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3853 WHERE `Id` = 1983; -- Drakkari Colossus
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3865 WHERE `Id` = 1984; -- Ionar
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3864 WHERE `Id` = 1985; -- Volkhan
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3866 WHERE `Id` = 1986; -- Loken
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3863 WHERE `Id` = 1987; -- General Bjarngrim
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3854 WHERE `Id` = 1988; -- Eck the Ferocious
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4614 WHERE `Id` = 1989; -- Amanitar
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4948 WHERE `Id` = 1990; -- Escaped from Arthas
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4897 WHERE `Id` = 1992; -- Falric
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4898 WHERE `Id` = 1993; -- Marwyn
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4768 WHERE `Id` = 1994; -- Krystallus
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3861 WHERE `Id` = 1995; -- Tribunal of Ages
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4769 WHERE `Id` = 1996; -- Maiden of Grief
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4770 WHERE `Id` = 1998; -- Sjonnir the Ironshaper
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4852 WHERE `Id` = 1999; -- Forgemaster Garfrost
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4861 WHERE `Id` = 2000; -- Scourgelord Tyrannus
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4860 WHERE `Id` = 2001; -- Krick
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4688 WHERE `Id` = 2002; -- Meathook
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4690 WHERE `Id` = 2003; -- Chrono-Lord Epoch
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4689 WHERE `Id` = 2004; -- Salram the Fleshcrafter
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4691 WHERE `Id` = 2005; -- Mal'ganis
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4859 WHERE `Id` = 2006; -- Bronjahm
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4424 WHERE `Id` = 2007; -- Devourer of Souls
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 12597 WHERE `Id` = 2008; -- Helya
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3692 WHERE `Id` = 2009; -- Anomalus
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3691 WHERE `Id` = 2010; -- Grand Magus Telestra
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3694 WHERE `Id` = 2011; -- Keristrasza
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3693 WHERE `Id` = 2012; -- Ormorok the Tree-Shaper
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3873 WHERE `Id` = 2013; -- Ley-Guardian Eregos
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3872 WHERE `Id` = 2014; -- Mage-Lord Urom
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3871 WHERE `Id` = 2015; -- Varos Cloudstrider
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3869 WHERE `Id` = 2016; -- Drakos the Interrogator
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 12613 WHERE `Id` = 2017; -- Viz'aduum the Watcher
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3833 WHERE `Id` = 2018; -- Second Prisoner
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3828 WHERE `Id` = 2019; -- First Prisoner
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3836 WHERE `Id` = 2020; -- Cyanigosa
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4363 WHERE `Id` = 2021; -- The Black Knight
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4361 WHERE `Id` = 2022; -- Grand Champions
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4362 WHERE `Id` = 2023; -- Argent Champion
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4772 WHERE `Id` = 2024; -- Skarvold & Dalronn
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4771 WHERE `Id` = 2025; -- Ingvar the Plunderer
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4773 WHERE `Id` = 2026; -- Prince Keleseth
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4775 WHERE `Id` = 2027; -- Gortok Palehoof
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3808 WHERE `Id` = 2028; -- King Ymiron
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 3809 WHERE `Id` = 2029; -- Skadi the Ruthless
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 4774 WHERE `Id` = 2030; -- Svala Sorrowgrave
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 12670 WHERE `Id` = 2031; -- Nightbane
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 12773 WHERE `Id` = 2032; -- Goroth
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 12815 WHERE `Id` = 2036; -- Harjatan
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 12861 WHERE `Id` = 2037; -- Mistress Sassz'ine
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 12863 WHERE `Id` = 2038; -- Fallen Avatar
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 12865 WHERE `Id` = 2039; -- Mephistroth
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 12996 WHERE `Id` = 2048; -- Demonic Inquisition
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 13019 WHERE `Id` = 2049; -- Primal Rage of Frost
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 13026 WHERE `Id` = 2050; -- Sisters of the Moon
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 12967 WHERE `Id` = 2051; -- Kil'jaeden
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 13123 WHERE `Id` = 2052; -- Maiden of Vigilance
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 13131 WHERE `Id` = 2053; -- Domatrax
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 13139 WHERE `Id` = 2054; -- The Desolate Host
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 13121 WHERE `Id` = 2055; -- Agronox
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 13122 WHERE `Id` = 2057; -- Thrashbite the Scornful
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 0 WHERE `Id` = 2059; -- Fury of the God Queen
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 13507 WHERE `Id` = 2063; -- Aggramar
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 13517 WHERE `Id` = 2064; -- Portal Keeper Hasabel
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 13543 WHERE `Id` = 2065; -- Zuraal the Ascended
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 13547 WHERE `Id` = 2066; -- Saprish
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 13551 WHERE `Id` = 2067; -- Viceroy Nezhar
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 13534 WHERE `Id` = 2068; -- L'ura
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 13536 WHERE `Id` = 2069; -- Varimathras
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 13553 WHERE `Id` = 2070; -- Antoran High Command
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 13593 WHERE `Id` = 2073; -- The Coven of Shivarra
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 13560 WHERE `Id` = 2074; -- Felhounds of Sargeras
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 13565 WHERE `Id` = 2075; -- The Defense of Eonar
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 13571 WHERE `Id` = 2076; -- Garothi Worldbreaker
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 0 WHERE `Id` = 2079; -- Keeper Aedis
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 0 WHERE `Id` = 2080; -- Void-Blade Zedaat
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 0 WHERE `Id` = 2081; -- Imp Mother
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 13788 WHERE `Id` = 2082; -- Imonar the Soulhunter
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 0 WHERE `Id` = 2083; -- Mistress Alluradel
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 13812 WHERE `Id` = 2084; -- Priestess Alun'za
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 13814 WHERE `Id` = 2085; -- Vol'kaal
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 13816 WHERE `Id` = 2086; -- Rezan
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 13818 WHERE `Id` = 2087; -- Yazma
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 13576 WHERE `Id` = 2088; -- Kin'garoth
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 14017 WHERE `Id` = 2092; -- Argus the Unmaker
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 14137 WHERE `Id` = 2093; -- Skycap'n Kragg
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 14139 WHERE `Id` = 2094; -- Council o' Captains
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 14141 WHERE `Id` = 2095; -- Ring of Booty
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 14143 WHERE `Id` = 2096; -- Lord Harlan Sweete
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 14405 WHERE `Id` = 2097; -- Sergeant Bainbridge
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 14403 WHERE `Id` = 2098; -- Chopper Redhook
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 14406 WHERE `Id` = 2099; -- Hadal Darkfathom
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 14408 WHERE `Id` = 2100; -- Viq'Goth
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 14419 WHERE `Id` = 2101; -- The Sand Queen
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 14421 WHERE `Id` = 2102; -- Jes Howlis
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 14423 WHERE `Id` = 2103; -- Knight Captain Valyri
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 14425 WHERE `Id` = 2104; -- Overseer Korgus
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 14432 WHERE `Id` = 2105; -- Coin-Operated Crowd Pummeler
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 14435 WHERE `Id` = 2106; -- Azerokk
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 14437 WHERE `Id` = 2107; -- Rixxa Fluxfume
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 14439 WHERE `Id` = 2108; -- Mogul Razdunk
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 14441 WHERE `Id` = 2109; -- Dread Captain Lockwood
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 14522 WHERE `Id` = 2111; -- Elder Leaxa
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 14554 WHERE `Id` = 2112; -- Sporecaller Zancha
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 14549 WHERE `Id` = 2113; -- Heartsbane Triad
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 14553 WHERE `Id` = 2114; -- Soulbound Goliath
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 14557 WHERE `Id` = 2115; -- Raal the Gluttonous
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 14560 WHERE `Id` = 2116; -- Lord and Lady Waycrest
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 14563 WHERE `Id` = 2117; -- Gorak Tul
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 14597 WHERE `Id` = 2118; -- Cragmaw the Infested
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 0 WHERE `Id` = 2121; -- T'zane
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 14696 WHERE `Id` = 2122; -- G'huun
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 14694 WHERE `Id` = 2123; -- Unbound Abomination
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 14715 WHERE `Id` = 2124; -- Adderis and Aspix
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 14718 WHERE `Id` = 2125; -- Merektha
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 14721 WHERE `Id` = 2126; -- Galvazzt
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 14724 WHERE `Id` = 2127; -- Avatar of Sethraliss
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 14736 WHERE `Id` = 2128; -- Fetid Devourer
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 6558 WHERE `Id` = 2129; -- Gekkan
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 14861 WHERE `Id` = 2130; -- Aqu'sirr
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 14862 WHERE `Id` = 2131; -- Tidesage Council
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 14864 WHERE `Id` = 2132; -- Lord Stormsong
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 14866 WHERE `Id` = 2133; -- Vol'zith the Whisperer
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 14892 WHERE `Id` = 2134; -- Vectis
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 14894 WHERE `Id` = 2135; -- Mythrax
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 14895 WHERE `Id` = 2136; -- Zek'voz
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 14931 WHERE `Id` = 2139; -- The Golden Serpent
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 15039 WHERE `Id` = 2140; -- The Council of Tribes
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 15059 WHERE `Id` = 2141; -- MOTHER
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 15062 WHERE `Id` = 2142; -- Mchimba the Embalmer
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 15168 WHERE `Id` = 2143; -- King Dazar
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 15170 WHERE `Id` = 2144; -- Taloc
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 15205 WHERE `Id` = 2145; -- Zul
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 0 WHERE `Id` = 2146; -- Raid Boss Dummy (15 Sec)
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 0 WHERE `Id` = 2147; -- Warbringer Yenajz
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 0 WHERE `Id` = 2148; -- Hailstone Construct
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 0 WHERE `Id` = 2149; -- Ji'arak
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 0 WHERE `Id` = 2252; -- The Lion's Roar
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 0 WHERE `Id` = 2253; -- Doom's Howl
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 0 WHERE `Id` = 2254; -- Raid Boss Dummy (5min)
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 16217 WHERE `Id` = 2257; -- Tussle Tonks
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 16219 WHERE `Id` = 2258; -- K.U.-J.0.
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 16221 WHERE `Id` = 2259; -- Machinist's Garden
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 16223 WHERE `Id` = 2260; -- King Mechagon
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 16563 WHERE `Id` = 2263; -- Grong
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 16560 WHERE `Id` = 2265; -- Champion of the Light
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 16562 WHERE `Id` = 2266; -- Jadefire Masters
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 16310 WHERE `Id` = 2268; -- Conclave of the Chosen
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 16316 WHERE `Id` = 2269; -- The Restless Cabal
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 16433 WHERE `Id` = 2271; -- Opulence
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 16475 WHERE `Id` = 2272; -- King Rastakhan
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 16542 WHERE `Id` = 2273; -- Uu'nat, Harbinger of the Void
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 16567 WHERE `Id` = 2276; -- Mekkatorque
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 16568 WHERE `Id` = 2280; -- Stormwall Blockade
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 16569 WHERE `Id` = 2281; -- Lady Jaina Proudmoore
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 16563 WHERE `Id` = 2284; -- Grong the Revenant
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 16562 WHERE `Id` = 2285; -- Jadefire Masters
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 17142 WHERE `Id` = 2289; -- Blackwater Behemoth
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 17145 WHERE `Id` = 2290; -- King Gobbamak
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 17161 WHERE `Id` = 2291; -- HK-8 Aerial Oppression Unit
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 17163 WHERE `Id` = 2292; -- Gunker
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 17182 WHERE `Id` = 2293; -- Za'qul
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 17305 WHERE `Id` = 2298; -- Abyssal Commander Sivara
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 17306 WHERE `Id` = 2299; -- Queen Azshara
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 17342 WHERE `Id` = 2303; -- Orgozoa
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 17371 WHERE `Id` = 2304; -- Lady Ashvane
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 17399 WHERE `Id` = 2305; -- Radiance of Azshara
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 17451 WHERE `Id` = 2311; -- The Queen's Court
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 17680 WHERE `Id` = 2312; -- Trixie & Naeno
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 0 WHERE `Id` = 2317; -- Ulmath, the Soulbinder
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 0 WHERE `Id` = 2318; -- Wekemara
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18048 WHERE `Id` = 2319; -- Memories of Azeroth: Burning Crusade
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18047 WHERE `Id` = 2320; -- Memories of Azeroth: Cataclysm
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18046 WHERE `Id` = 2321; -- Memories of Azeroth: Wrath of the Lich King
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18064 WHERE `Id` = 2325; -- Tunk
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18066 WHERE `Id` = 2326; -- Ravnyr
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18071 WHERE `Id` = 2327; -- Maut
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18073 WHERE `Id` = 2328; -- Dark Inquisitor Xanesh
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18083 WHERE `Id` = 2329; -- Wrathion
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18085 WHERE `Id` = 2331; -- Ra-den the Despoiled
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18015 WHERE `Id` = 2332; -- Thrall the Corrupted
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18117 WHERE `Id` = 2333; -- The Hivemind
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18116 WHERE `Id` = 2334; -- Prophet Skitra
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18123 WHERE `Id` = 2335; -- Shad'har the Insatiable
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18130 WHERE `Id` = 2336; -- Vexiona
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18147 WHERE `Id` = 2337; -- Carapace of N'Zoth
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18015 WHERE `Id` = 2338; -- Alleria Windrunner
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18179 WHERE `Id` = 2343; -- Drest'agath
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18211 WHERE `Id` = 2344; -- N'Zoth the Corruptor
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18224 WHERE `Id` = 2345; -- Il'gynoth, Corruption Reborn
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 0 WHERE `Id` = 2351; -- Grand Empress Shek'zara
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 0 WHERE `Id` = 2352; -- Tashara
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 0 WHERE `Id` = 2353; -- Vuk'laz the Earthbreaker
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18606 WHERE `Id` = 2356; -- Ventunax
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18607 WHERE `Id` = 2357; -- Kin-Tara
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18608 WHERE `Id` = 2358; -- Oryphrion
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18609 WHERE `Id` = 2359; -- Devos, Paragon of Loyalty
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18629 WHERE `Id` = 2360; -- Kryxis the Voracious
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18628 WHERE `Id` = 2361; -- Executor Tarvold
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18627 WHERE `Id` = 2362; -- Grand Proctor Beryllia
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18630 WHERE `Id` = 2363; -- General Kaal
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18652 WHERE `Id` = 2364; -- Kul'tharok
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18654 WHERE `Id` = 2365; -- Gorechop
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18656 WHERE `Id` = 2366; -- Xav the Unfallen
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18699 WHERE `Id` = 2370; -- Rexxar
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18704 WHERE `Id` = 2371; -- Inquisitor Gnshal
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18705 WHERE `Id` = 2372; -- Oblivion Elemental
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18706 WHERE `Id` = 2373; -- Vez'okk the Lightless
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18707 WHERE `Id` = 2374; -- Therum Deepforge
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18708 WHERE `Id` = 2375; -- Slavemaster Ul'rok
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18709 WHERE `Id` = 2376; -- Overlord Mathias Shaw
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18710 WHERE `Id` = 2377; -- Magister Umbric
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18773 WHERE `Id` = 2380; -- Echelon
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18775 WHERE `Id` = 2381; -- Lord Chamberlain
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18778 WHERE `Id` = 2382; -- Globgrog
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18780 WHERE `Id` = 2383; -- Hungering Destroyer
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18781 WHERE `Id` = 2384; -- Doctor Ickus
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18783 WHERE `Id` = 2385; -- Domina Venomblade
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18785 WHERE `Id` = 2386; -- Stradama Margrave
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18788 WHERE `Id` = 2387; -- Blightbone
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18789 WHERE `Id` = 2388; -- Amarth, The Harvester
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18794 WHERE `Id` = 2389; -- Stichflesh
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18790 WHERE `Id` = 2390; -- Nalthor the Rimebinder
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18802 WHERE `Id` = 2391; -- An Affront of Challengers
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18805 WHERE `Id` = 2392; -- Mistcaller
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18808 WHERE `Id` = 2393; -- Tred'ova
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18812 WHERE `Id` = 2394; -- The Manastorms
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18815 WHERE `Id` = 2395; -- Hakkar, the Soulflayer
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18817 WHERE `Id` = 2396; -- Mueh'zala
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18819 WHERE `Id` = 2397; -- Ingra Maloch
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 19396 WHERE `Id` = 2398; -- Shriekwing
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 19415 WHERE `Id` = 2399; -- Sludgefist
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18824 WHERE `Id` = 2400; -- Dealer Xy'exa
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 18810 WHERE `Id` = 2401; -- Halkias, the Sin-Stained Goliath
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 19029 WHERE `Id` = 2402; -- Sun King's Salvation
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 19047 WHERE `Id` = 2403; -- High Adjudicator Aleez
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 19056 WHERE `Id` = 2404; -- Mordretha
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 19146 WHERE `Id` = 2405; -- Artificer Xy'mox
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 19158 WHERE `Id` = 2406; -- Lady Inerva Darkvein
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 19208 WHERE `Id` = 2407; -- Sire Denathrius
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 0 WHERE `Id` = 2408; -- Nurgash Muckformed
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 0 WHERE `Id` = 2409; -- Oranomonos the Everbranching
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 0 WHERE `Id` = 2410; -- Mortanis
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 0 WHERE `Id` = 2411; -- Valinor
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 19279 WHERE `Id` = 2412; -- The Council of Blood
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 19342 WHERE `Id` = 2415; -- Ember Court
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 0 WHERE `Id` = 2416; -- Nathanos Blightcaller
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 19388 WHERE `Id` = 2417; -- Stone Legion Generals
UPDATE `instance_dungeon_encounters` SET `CompleteWorldStateID` = 19410 WHERE `Id` = 2418; -- Huntsman Altimor

