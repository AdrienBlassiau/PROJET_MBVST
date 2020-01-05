Copyright (c) 2019-2020, Adrien BLASSIAU

Permission to use, copy, modify, and/or distribute this software
for any purpose with or without fee is hereby granted, provided
that the above copyright notice and this permission notice appear
in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR
CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

# Projet 

Auteur: 

*  Adrien BLASSIAU (adrien.blassiau@ensiie.fr)

      
IMPORTANT: LIRE CE FICHIER AVANT DE LANCER LE PROGRAMME



  Sommaire
===============================================================================

1. Introduction
2. Instructions d'installation des différents outils
3. Conseils d'utilisation



1. Introduction                 
===============================================================================

Ceci est le README du projet d'OPTI2.

NOTE: Je vous invite à lire le rapport qui vous renseignera sur la démarche et les choix engagés dans ce projet.


2. Instructions d'installation des différents outils pour l'exécution du code
===============================================================================


**Utilisateur Linux**


*******************************************************************************

Doxygen
--------

Doxygen est un outil qui permet de gérer la documentation de son code. Il permet à terme de fournir une page web ou un pdf contenant la documentation du code que le développeur souhaite publier.

**Entrez dans votre console** : 
> sudo apt-get install doxygen

*******************************************************************************

CUnit
--------

CUnit est une bibliothèque de tests unitaires pour C. Elle permet de programmer des tests, de les exécuter, et d’afficher un résumé des tests réussis ou échoués. Un test unitaire ne teste qu’une partie atomique des spécifications sous des conditions précises qui, bien généralement, ne couvrent pas tous les cas.

**Entrez dans votre console** : 
> sudo apt-get install libcunit1 libcunit1-doc libcunit1-dev


3. Conseils d'utilisation
===============================================================================

Voici différentes commandes qui vous permettrons d'observer des résultats et informations sur le travail effectué :


Lancer le code principal
------------------------

Pour lancer le code principal, entrez la commande suivante à la racine du projet :

**1. Entrez dans votre console** : 
> make && ./bin/main

L’exécutable est déjà généré, vous n'êtes pas obligé de recompiler avec make. Enfin, tout l'output de l’exécutable est disponible dans output.txt qui contient en plus les graphes générés de grandes tailles (dépassant la taille du terminal ...) et des résultats sur un PL que j'ai laissé tourner plus de trois heures.


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

Pour obtenir l'ensemble des résultats des tests unitaires : 

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
