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
        - 8 Caractère originaux par frame max
          - Caractère originaux de 5 x 8 pixels

- ### Développement

  - 8 Caractère originaux par frame max
    - Utilisation de C++ sans toutes les librairies standard

---

## Compte rendu

- _**Materiel**_
  - [x] Arduino

---

- _**Personnes**_
  - [x] Nathan
  - [x] Rémi
  - [x] Dimitri
  - [x] Lucas


---

- ### **Travail fait**

Nous avons réalisé ce projet en plusieurs parties. Nous nous sommes d'abord intéressés à la création des sprites des vaisseaux, obstacles, missiles, etc. Ensuite, nous avons entammé le processus de programmation, qui s'est avéré très laborieux du fait que notre code source est divisé en 4 fichiers header (.h), 1 fichier source (.cpp) et in fichier arduino (.ino). Ce faisant, le code est plus lisible mais le compilateur ainsi qu'intelli-sense (autocomplétion) nous ont posé beaucoup de problèmes, ralentissant notre progression.

Nous avons crée et utilisé des objets c++, avec des classes pour les entités, des constructeurs et de l'héritage entre les classes. Le jeu comporte donc le joueur, des obstacles indestructibles et agressifs. S'il est touché par un obstacle agressif le joueur perd 1 point de vie. De plus il est aussi possible de récupérer des humains pour augmenter son score. Les obstacles et bonus apparaissent aléatoirement au fur et à mesure de la partie.



Tous les designs de notre jeu ont été imaginés de sorte à le rendre aussi attrayant qu’intuitif.

Nous avons tout d’abord pensé au design du vaisseau. Sa forme triangulaire indique clairement l’avant du vaisseau du fait de sa pointe (_qui s’agrandit lors du rechargement du canon_) **Pas implémenté**, mais également l’arrière, grâce au design pensé pour faire des propulseurs.

Nous devions faire un ennemi qui tire. De ce fait, nous avons fait un alien tentaculaire (_alternant la position de ses tentacules du haut avec celles du bas afin de donner une logique dans son déplacement_) **Pas implémenté**. Nous l’avons pensé avec des yeux au centre de sa forme afin de le rendre facilement identifiable par le joueur. Les tirs de l’alien ont été fait en forme d’éclair pour accentuer le côté extraterrestre mais également permettre au joueur d’identifier clairement et rapidement ses tirs des tirs ennemis.

À présent, qui dit ennemi qui tire dit également ami à sauver. Or, comme nous sommes un héros de la Terre luttant contre des aliens, nous avons pensé à sauver ses pauvres terriens kidnappés par les terribles aliens. En effet, les humains sont l’objectif à sauver afin de gagner des points, la forme humaine ainsi que _les mouvements d’appels à l’aide_ (**Pas implémentés**) sont là pour les différencier facilement du reste et surtout à ne pas les confondre avec les ennemis.

Il nous fallait à présent un obstacle à esquiver et quoi de mieux qu’un satellite ? En effet, notre héro terrien élimine les terribles aliens en orbite autour de la Terre mais, il faut faire attention à ne pas détruire ou se crasher sur les satellites sinon, plus d’émissions à la télévision, plus de 4G, plus d’internet, bref, l’apocalypse. C’est pourquoi, le satellite est un choix évident pour que le joueur sache intuitivement qu’il faut les esquiver et non les détruire.

_(Comment savoir que l’on a bien éliminé un ennemi ? En le voyant exploser à cause de notre tir de canon ainsi, le joueur a la certitude que l’alien est bien mort (ou l’humain s’il fait un mauvais tir) s’il ne le voit pas mort or, l’explosion est parfaite pour cela.)_ **Pas implémenté**

Enfin, nous avons mis un tableau des scores pour vous pousser à vous améliorer à chaque partie, mais également à avoir ce sentiment d’accomplissement d’avoir fait mieux qu’avant. Nous avons aussi mis des vies en forme de cœur car, même si cela est très classique, ça reste très efficace et nous n’avions pas assez de pixels pour vraiment faire mieux.
