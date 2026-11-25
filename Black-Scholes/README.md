# Black-Scholes
Le modèle de Black-Scholes (1973) est très utilisé en finance. Il prend 5 paramètres : 
- Le prix actuel du sous-jacent (S)
- Le prix d'exercice ou Strike (K)
- Le taux d'intérêt sans risque (r)
- La volatilité de l'actif (sigma)
- Le temps restant avant l'échéance (T)

## Equipe
Thomas Dégremont

## Structure du projet
* `src/` : Fichiers sources `.cpp`, `.h`
* `obj/` : Fichiers objet `.o`
* `bin/` : Executable générés
* `doc/` : Documentation du projet
*Makefile
*Readme.md

## Compilation et Installation

### Prérequis
* Un compilateur C++ (g++)
* Make

### Installation et lancement

### Cloner le dépôt
```
git clone https://github.com/thomasdgm/Black-Scholes
```
### Aller dans le dossier
```
cd Black-Scholes
```

Le projet utilise un Makefile

### Lancer la version Txt
```
make
./bin/BlackScholes
```

### Générer la documentation
```
make doc
```

### supprimer les fichiers objets et les executables
```
make clean
```

# Fonctionnalité du projet
Ce moteur quantitatif développé en C++ permet de calculer le prix théorique d'une option, il intègre également :
- Le calcul des grecs (mesure de sensibilité du prix face aux variations des paramètres du marché)
    - Delta et Gamma : Sensibilité au prix du sous-jacent
    - Vega : Sensibilité à la volatilité
    - Theta : Impact du temps qui passe
    - Rho : Sensibilité aux taux d'intérêt
- Un solveur numérique basé sur la méthode de **Newton-Raphson**.
    À partir d'un prix observé sur le marché, le programme inverse le modèle de Black-Scholes pour extraire la volatilité anticipée par les acteurs du marché.
