﻿///////////////////////////////////////////////////////////////////////////
// Author: Martial TOLA
// Year: 2010-2011-2012-2013-2014-2015
// CNRS-Lyon, LIRIS UMR 5205
///////////////////////////////////////////////////////////////////////////

Marche à suivre pour Mepp (32 bits) sous Windows avec Visual Studio Express 2008 SP1 :
--------------------------------------------------------------------------------------


1a) récupérer et installer DAEMON Tools Lite afin de pouvoir installer les images 'iso' des logiciels ci-dessous:
http://download.gforge.liris.cnrs.fr/meppbin/windows/utils/ (DTLitexxxx-yyyy.exe)

1b) récupérer et installer Visual Studio Express 2008 SP1:
http://download.gforge.liris.cnrs.fr/meppbin/windows/vs2008/VS2008ExpressWithSP1FRAx1504731.iso (869 Mo)

2a) récupérer les dépendances du projet MEPP (headers & libs, CMake & CMake-gui):
http://download.gforge.liris.cnrs.fr/meppbin/windows/vs2008/MEPP/mepp_prebuilt_binaries_vs2008_x86_v02.rar (497 Mo)
et décompresser l'archive dans le répertoire de votre choix (exemple: C:\dev32 - Attention, ne pas utiliser un chemin 'exotique' du type "Documents and Settings\$USER$\My ...\My ...")

2b) récupérer la mise à jour des dépendances du projet MEPP (support vidéo ffmpeg):
http://download.gforge.liris.cnrs.fr/meppbin/windows/vs2008/MEPP/mepp_prebuilt_binaries_vs2008_x86_ffmpeg_addon.rar (9 Mo)
et décompresser l'archive dans le même répertoire que ci-dessus (si besoin, répondre oui pour écraser des fichiers)

3a) positionner 3 variables d’environnement (menu « Poste de travail » -> bouton droit -> Propriétés -> onglet « Avancé » -> bouton « Variables d’environnement » (en bas) -> puis dans la partie « Variables système » (en bas):
 - bouton « nouveau » : rajouter la variable QTDIR avec comme valeur :
C:\dev32\Qt_4.6.3_x86 si vous avez décompressé le fichier ci-dessus dans C:\dev32
 - bouton « nouveau » : rajouter la variable CGAL_DIR avec comme valeur :
C:\dev32\CGAL-3.6.1_x86 si vous avez décompressé le fichier ci-dessus dans C:\dev32
 - bouton « modifier » : rajouter au sein (à la fin par exemple) de la variable Path:
;C:\dev32\Qt_4.6.3_x86\bin (attention au ;)

Note: il se peut que vous disposiez d'un autre logiciel (exemple: MiKTeX) utilisant une autre version de Qt (et donc des dll incompatibles) ce qui provoquera une erreur au lancement de Mepp.
Dans ce cas, il faut donc changer l'ordre de votre variable Path et positionner C:\dev32\Qt_4.6.3_x86\bin avant le logiciel en question.

3b) installer Graphviz : http://download.gforge.liris.cnrs.fr/meppbin/windows/utils/ (graphviz-x.yy.z.msi)

Note: Graphviz est utilisé par Doxygen pour la génération des images des graphes de dépendances. C'est l'outil 'dot.exe' qui est appelé.
Mais, si vous avez préalablement installé MATLAB, celui-ci utilise lui aussi un outil 'dot.exe' ce qui posera problème et aura pour conséquence d'avoir des images 'vides'.
Dans ce cas, il faut donc changer l'ordre de votre variable Path et positionner Graphviz avant MATLAB.

3c) redémarrer la machine pour la prise en compte des variables d'environnement ci-dessus

4) utiliser CMake-gui (dans C:\dev32\_cmake-2.8.3.20110118_\bin)
 - renseigner le champ "Where is the source code" avec C:\MEPP.git (ou/or MEPP.svn)\MEPP (attention, pas C:\MEPP.git (ou/or MEPP.svn)\MEPP\src !)
 - renseigner le champ "Where to build the binaries" avec C:\MEPP.git (ou/or MEPP.svn)\MEPP\build
 - cliquer sur Configure (en bas à gauche) et choisir comme 'Generator': "Visual Studio 9 2008"
 - activer/désactiver les composants que vous désirez ou non (premières lignes en haut toujours du type BUILD_component_nomducomposant, exemple: BUILD_component_Curvature)
 - cliquer sur Configure (en bas à gauche) à nouveau
 - cliquer sur Generate (en bas à gauche)
 - ouvrir avec Visual Studio la solution mepp.sln générée dans C:\MEPP.git (ou/or MEPP.svn)\MEPP\build puis compiler Mepp
 - se positionner sur le "sous-projet" mepp, faire un "bouton droit" puis cliquer sur "Définir comme projet de démarrage"
 
Note: attention, par défaut le projet se compile en Debug, à vous de basculer en Release si vous le souhaitez.

5) la documentation de Mepp et de votre composant au format Doxygen se génère également via Visual Studio