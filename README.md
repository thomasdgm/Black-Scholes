# Black-Scholes
Le modèle de Black-Scholes (1973) est très utilisé en finance. Il prend 5 paramètres : 
- Le prix actuel du sous-jacent (S)
- Le prix d'exercice ou Strike (K)
- Le taux d'intérêt sans risque (r)
- La volatilité de l'actif (sigma)
- Le temps restant avant l'échéance (T)

## Fonctionnalités
- **Valorisation théorique :** Calcul du prix des options européennes **Call** et **Put**.
- **Calcul des Grecs :**
  - **Delta ($\Delta$) & Gamma ($\Gamma$) :** Sensibilité et convexité par rapport au prix du sous-jacent.
  - **Vega ($\nu$) :** Sensibilité à une variation de $+1\,\%$ de la volatilité.
  - **Theta ($\Theta$) :** Décroissance temporelle par jour calendaire.
  - **Rho ($\rho$) :** Sensibilité à une variation de $+1\,\%$ du taux sans risque.
- **Dashboard interactif (Streamlit & Plotly) :**
  - Calcul dynamique de la *Moneyness* ($S/K$).
  - Graphiques de payoff à maturité pour les stratégies **Covered Call** et **Protective Put** avec suivi du spot en temps réel.

## Auteur
Thomas Dégremont

## Structure du projet
```text
Black-Scholes/
├── src/               # Fichiers sources C++ (.cpp, .h)
├── obj/               # Fichiers objets compilés (.o)
├── bin/               # Exécutable de test et bibliothèque partagée (.dll / .so)
├── doc/               # Documentation générée (Doxygen)
├── cpp_bridge.py      # Pont Python / C++ via ctypes
├── app.py             # Interface graphique Streamlit
├── Makefile           # Automatisation de la compilation
└── README.md
```

## Compilation et Installation

### Prérequis
* Un compilateur C++ (g++)
* Make
* Python 3.11+ avec streamlit et plotly

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

### Lancement
```
make
streamlit run app.py
```

### Générer la documentation
```
make doc
```

### supprimer les fichiers objets et les exécutables
```
make clean
```
