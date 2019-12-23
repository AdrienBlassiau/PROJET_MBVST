# Projet 

Auteur: 

*  Adrien BLASSIAU (adrien.blassiau@ensiie.fr)

      
IMPORTANT: LIRE CE FICHIER AVANT DE LANCER LE PROGRAMME



  Sommaire
==================================================================================

1. Introduction
2. Instructions d'installation des différents outils
3. Conseils d'utilisation



1. Introduction                 
==================================================================================

Ceci est le README du projet de PROG2 associé au Challenge **Monotonic Segments and GHC Sort**. Vous trouverez dans ce document toutes les informations nécessaires pour faire fonctionner le code.

NOTE: Nous vous invitons à lire notre rapport qui vous renseignera sur la démarche et les choix engagés dans ce projet.


2. Instructions d'installation des différents outils pour l'exécution du code
==================================================================================


**Utilisateur Linux**


*********************************************************************************************

Doxygen
--------

Doxygen est un outil qui permet de gérer la documentation de son code. Il permet à terme de fournir une page web ou un pdf contenant la documentation du code que le développeur souhaite publier.

**Entrez dans votre console** : 
> sudo apt-get install doxygen

*********************************************************************************************

CUnit
--------

CUnit est une bibliothèque de tests unitaires pour C. Elle permet de programmer des tests, de les exécuter, et d’afficher un résumé des tests réussis ou échoués. Un test unitaire ne teste qu’une partie atomique des spécifications sous des conditions précises qui, bien généralement, ne couvrent pas tous les cas.

**Entrez dans votre console** : 
> sudo apt-get install libcunit1 libcunit1-doc libcunit1-dev


3. Conseils d'utilisation
==================================================================================

Voici différentes commandes qui vous permettrons d'observer des résultats et informations sur le travail effectué :


Lancer l'analyse statique du code
------------------------

Pour lancer l'analyse statique du code associé aux différentes parties du projet, entrez les commandes suivantes à la racine du projet

**1. Entrez dans votre console** : 
> frama-c-gui -wp -wp-rte -wp-timeout 20 src/monotonic_cutpoints.c

**2. Entrez dans votre console** : 
> frama-c-gui -wp -wp-rte -wp-timeout 20 src/monotonic_reverse.c

**3. Entrez dans votre console** : 
> frama-c-gui -wp -wp-rte -wp-timeout 20 src/merge.c


*********************************************************************************************

Doxygen
-------

Pour obtenir la documentation générée par Doxygen, un document sous format web est déjà présent dans le dossier fournit, pour l'ouvrir :

*Via navigateur fichier*

Il est présent dans doc/html/index.html Ouvrez le sur votre navigateur web favori.

*Via console*

**Entrez dans votre console** : 
> firefox doc/html/index.html &

NOTE: Remplacez firefox par votre navigateur web favori.

*Informations*

Vous pouvez aussi régénérer la documentation puis l'ouvrir : 

**Entrez dans votre console** :
> make doxygen && firefox doc/html/index.html &

 
*********************************************************************************************

Tests unitaires CUnit
---------------------

Pour obtenir l'ensemble des résultats de nos tests unitaires : 

**Entrez dans votre console** : 
> ./bin/test

*Informations*

Vous pouvez aussi régénérer l’exécutable de test : 

**Entrez dans votre console** :
> make test & ./bin/test

*Comment lire le résultat d'un test CUnit ?*

      CUnit - A unit testing framework for C - Version 2.1-3
      http://cunit.sourceforge.net/

    Run Summary:     Type  total    Ran Passed Failed  Inactive
                   suites      1      1    n/a      0         0
                    tests      5      5      5      0         0
                  asserts    118    118    118      0       n/a

    Elapsed time =    0.001 seconds


La ligne tests correspond au nombre de tests unitaires effectués, la ligne asserts correspond au nombres d'assertions vérifiées. Pour chaque tests, il peux y avoir plusieurs assertions. 

                                



*********************************************************************************************


*Merci pour votre lecture !*
