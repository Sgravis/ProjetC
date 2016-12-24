Partie 1: Pré-traitement des données
==

Pour pouvoir partager les données avec d’autres groupes du projet, il est important de protéger la vie privée des utilisateurs ayant collecté les traces. Pour se faire nous proposons dans cette partie de réaliser des pré-traitements sur les traces afin de générer des nouveaux fichiers de traces ayant supprimé des informations sensibles.

Les algorithmes proposés sont les suivants:
- [X] suppression de points dans un cercle donné (typiquement le domicile de l’utilisateur ou son bar favori)
- [X] suggestion de points d’intérêts à supprimer: il faut calculer des points pour lesquels on repère une fréquentation régulière et qui peut servir de centre pour un cercle
- [ ] suppression des points se rendant à un point d’intérêt c’est-à-dire une “route”
- [ ] calcul automatique du rayon d’un cercle à partir de la densité de population (en rase campagne, on imagine que les cercles ont des rayons de plusieurs kilomètres, en ville des centaines de mètres suffisent) en exploitant la base ADRESSE.


Partie 2: Visualisation des traces
==

Dans cette partie, on souhaite visualiser les traces de géolocalisation. La visualisation peut être statique ou dynamique et doit permettre d’apprécier les efforts faits dans la partie 1 (protection de la vie privée).

Les algorithmes proposés sont:

- [X] Visualisation statique:
	- [X] Vue d’une carte et de points représentants les mesures.
	- [ ] Aggrégation de points: les points redondants peuvent être fusionnés graphiquement pour représenter un taux de présence
	- [ ] Vue de routes en liant les points
	- [ ] Vue des points d’intérêts
	- [ ] Vue des cercles de protection de la vie privée
- [ ] Visualisation dynamique:
	- [ ] animation des points avec le temps; contrôle de la vitesse de rejeu
	- [ ] animation des routes, etc.
- [ ] Visualisation d’information contextuelle: la base ADRESSE peut permettre d’afficher l’adresse des points d’intérêt
- [ ] Visualisation multiple de traces: ce mode est particulièrement utile pour comparer les traces avant et après traitement et pouvoir se rendre compte visuellement de l’effet de protection de la vie privée apportée


Partie 3: Etude des données d’une population
==

Dans cette partie, on souhaite combiner un ensemble de traces de mobilités afin d’alimenter l’outil de visualisation avec des données de synthèse. Pour simplifier, une solution est de traiter n traces et d’en sortir différents fichiers contenant des informations agrégées. Les informations agrégées peuvent être:

- [ ] point d’intérêt avec un seuil (k personnes ont ce point parmi n)
- [ ] route fréquentées: des “zones” de type route sont fréquemment empruntées (par exemple Lahitolle)

Toutes ces données sont temporisées, c’est-à-dire que les points d’intérêt communs n’ont d’existence que sur certains laps de temps. Par exemple, il est douteux que l’INSA soit un point d’intérêt de 2h à 3h du matin… Il faut donc penser à toujours préciser le temps afin que l’outil de visualisation puisse faire des affichages dépendant du temps (faire disparaitre les “vieux” point d’intérêts).

Partie 4: visualisation multiple
==

Dans cette partie, l’outil de visualisation doit être enrichi avec les données calculées en partie 3.

- [ ] Visualisation des informations agrégées (points d’intérêt communs, routes, etc.)
- [ ] Animation d’une ou plusieurs traces, en même temps que les données agrégées. L’intérêt est de pouvoir par exemple voir les points d’intérêt d’une communauté (RU, INSA, etc.) et de regarder 1 individu et voir s’il se rend à ces points d’intérêts ou pas.


