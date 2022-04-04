# WOooo

## Colaborateur

**Nathan Eudeline** : `Bafbi#3144` -> _Dev_  
**Dimitri Stintzi** : `Lycaon#7287` -> _Game designer_  
**Rémi Hage** : `Slyvred#2729` -> _Dev_  
**Lucas Boutemy** : `Assassin Sith Akabane#1986` -> _Game designer_

---

## Description

Vous êtes un héros, excellent pilote terrien et vous poursuivez de terribles extraterrestres qui ont
dérobé les meilleurs [OBJECT_INDEFINI] de la terre. Les voleurs ont vu que vous les poursuivez à bord
de votre [VAISSEAU] et vous lancent obstacles et appâts pour freiner votre poursuite. Vous devez
sécuriser un maximum de [OBJECT_INDEFINI] tout en évitant les [OBSTACLE_INDESTRUCTIBLE] et en
interceptant à distance les [OBSTACLE_AGRESSIF] avec votre rayon laser.

---

## Tâche à accomplir

1. Concevoir un écran d’accueil animé (en attente d’un déclenchement par l’utilisateur)

2. Concevoir trois objets possibles [OBJECT_INDEFINI], [OBSTACLE_INDESTRUCTIBLE], [OBSTACLE_AGRESSIF] ainsi que le [VAISSEAU] et leurs design en pixel

3. Afficher tous les éléments sur l’écran lcd de la carte ISEN arduino:

    1. Vaisseau dans la zone bleue

    2. Score / points de vie (PV) possibles dans la zone verte

    3. Obstacles dans la zone jaune  

    ![Zone de jeu](https://cdn.discordapp.com/attachments/676180251155365893/960168126689992704/unknown.png)

4. Générer la séquence d’obstacles aléatoirement (différente d’une partie sur l’autre y compris après reset de la carte)

5. Organiser le déplacement du vaisseau en vertical avec deux boutons pour se placer sur la ligne du haut ou du bas

6. Déclencher le laser avec un bouton d’interruption (il s’affiche du vaisseau jusqu’au premier obstacle rencontré à l’horizontal de gauche à droite)

7. Implémenter le déplacement des obstacles de droite à gauche selon des pas de temps

8. Implémenter le gameplay :

    1. Un [OBSTACLE_AGRESSIF] doit être touché par un rayon laser avant d’arriver dans la colonne du vaisseau ce qui le retire. Dans le cas contraire le joueur perd un PV.

    2. Un vaisseau doit esquiver un [OBSTACLE_INDESTRUCTIBLE] en se plaçant sur la ligne qui ne le contient pas pendant le pas de temps ou il est sur la même colonne. Cet  obstacle est insensible au laser. Dans le cas contraire le joueur perd un PV.

    3. Un joueur doit être sur la même case que [OBJECT_INDEFINI] pendant le pas de temps ou il est sur la même colonne pour le sécuriser. Si l’objet est touché par un laser ou s’il sort de l’écran sans être sécurisé, le joueur perd un PV

    4. Un joueur qui arrive à 0PV termine la partie

    5. La durée d’un pas de temps diminue plus la partie prends du temps depuis une vitesse initiale jusqu’à une vitesse maximale raisonnable.

9. Allumer la led bleue lorsqu’il ne reste plus qu’un seul point de vie

10. Prévoir un écran indiquant la fin de la partie et le score avant de revenir à l’écran d’accueil

11. Utiliser le potentiomètre pour rajouter une notion de difficulté en réduisant le champ de vision. La zone marron de 0 à 9 cases de large sera affichée ou non selon la position du potentiomètre et pourra être réglée dès l’écran d’accueil avant le début de la partie.  
![Zone de jeu avec brouillard](https://cdn.discordapp.com/attachments/676180251155365893/960173874614509618/unknown.png)

12. Proposez un gameplay agréable en précisant le détail des réglages choisis :

    1. Vitesse min et max

    2. Rythme de variation de la vitesse de défilement

    3. Une évaluation du score selon les obstacles bien gérés et la difficulté courante (vitesse/brouillard)

    4. Les restrictions imposées à la génération aléatoire des objets pour rendre le jeu jouable

---

## Limitation

- ### Game Design

  - 4 Leds / Bouton (1~2 bouton d'interruption)
    - 1 Potentiomètre
    - 1 Ecran lcd
      - 16 x 2 Charactères
        - 8 Charactère originaux par frame max
          - Charactère originaux de 5 x 8 pixels

- ### Developpement

  - 8 Charactère originaux par frame max
    - Utilisation de C++ sans toute les librairies standard

---

## Journal d'avancement

### **Vendredi 1er Avril** _(01/04/22)_

- _**Materiel**_
  - [x] Arduino

---

- _**Personne**_
  - [x] Nathan
  - [x] Rémi
  - [x] Dimitri
  - [x] Lucas

---

- ### **Pensée**

  - Game design :  

  qdqdq

  - Dev :  
  
  qdqdq

---

- ### **Travail fait**
