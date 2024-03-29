# Règles de contribution au projet

## Objectif du document

Le présent document a pour rôle de définir les règles à suivre pour participer au projet.

## Règles de définition des tâches

Le "Projet" GitHub sert à référencer toutes les tâches à effectuer sur le projet,
Les tâches sont regroupées dans des "Milestones" qui sont les épiques à réaliser.

La notion d'"User Story" n'existe pas sur ce model car les tâches sont à granularité fine, car l'intégration d'une tâche doit se faire rapidement.

### Le template d'écriture des tickets

Les descriptions des tâches doivent respecter le format suivant :

```markdown
**Objectif**:

**Contraintes Imposées**:

**Norme de référence**:

**Conception préliminaire**:

**Maquettes**:

**Livrables attendus**:

**Documentations attendus**:

**Tests attendus**:

```

### Les critère de passage de la tâche à "prêt à commencer"

Pour qu'une tâche soit prête à commencer elle doit:

- avoir une description complète qui respecte le template.
- avoir le repository associé à la tâche.
- avoir un "épique" associé à la tâche.
- avoir le statut "TO DO".
- ne pas avoir de blocant.

### Le pattern d'ouverture de la branche

La branche git doit être crée à partir du ticket, avec les patterns suivants :

 - feature/* pour les ajouts fonctionnels
 - bugfix/* pour les corrections de bug
 - hotfix/* pour les ajustements rapides qui ne sont pas des bugs
 - documentation/* pour les ajouts ou modifications documentaires

### Les critères de clôture de la tâche

- les livrables doivent être réalisés.
- la documentation doit être rédigée.
- la chaîne d'intégration continu doit être passée avec succès.
- l'analyse sonar doit être revue.

### Les livrables attendus

Les livrables sont les éléments nouveaux à produire pendant la tâche, il peut s'agir d'un ou plusieurs morceau de code, d'un script, d'une ressource à créer ou encore d'une documentation.

### L'importance de la documentation

La documentation doit etre detaillé pour garantir le maintient de l'application même après plusieurs mois de gêle des activités

Chaque tâche crée doit notifier clairement la documentation associée, des tâches peuvent également être exclusivement documentaires pour ne pas impacter le déroulement de la progression de l'application.

### Le rôle des tests

Les tests ont plusieurs rôle, le principal rôle et d'éviter les régressions dû à des mises à jour de version des dépendances.

> Voir la documentation des tests pour plus de détails.

### Les critères de priorisation des tâches

Les tâches sont triées par priorité `Critical`, `Highest`, `High`, `Low` et `Lowest`.

Les tâches `Critical` sont les tâches qui ont des impacts bloquants une ou plusieurs autres tâches, elles ont généralement un impact significatif sur le projet et sont donc a traiter au plus tôt quand c'est possible.

Les autres niveaux sont un ordre de priorisation par la plus value de la tâche pour l'application.

> La priorité n'est qu'un classement indicatif, les tâches sont réalisées par opportunité, le temps consacré à la progression du projet est très réduit, les temps libre de courte periode sont alloués aux tâches prêtes et facilement réalisable. Quand des temps libres sont conséquent c'est l'ordre de priorité qui s'applique. 

## Règles de gestion des versions

La gestion de version de l'application se fait avec git, le système d'hébergement choisi pour le repository est GitHub.

Le pattern de version choisi est `X.Y.Z`.

- `X` est modifié pour une mise à jour importantes qui intègre de nouvelles fonctionnalités ou une mise à jour de dependance importante.
- `Y` est modifié quand la mise à jour de l'interface CLI.
- `Z` est modifié quand du code source est modifié sans impact fonctionnel ou CLI.

### L'usage de git en locale

En local l'usage de git se fait sur la stratégie du rebase fast forward et du squash commit.

Des hooks sont mis en place:

- pre-commit : pour formater le code avant le commit (clang-format pour le c++ et prettier pour le reste)

### L'usage de git avec GitHub

Avec GitHub certains fonctionnements sont disponibles mais à utiliser avec parcimonie comme la mise à jour de demande de tirage qui engendre un commit de fusion et non rebase.

#### les autorisations d'écriture dans l'intégration continu

Les dépendances se mettent automatiquement à jour quand l'intégration continue d'une demande de tirage se termine avec succès.

Les dépendances qui se mettent à jour sont:

- les plug-ins GitHub actions

Dans les demandes de tirage les fichiers sont automatiquement formatés avec les mêmes configurations qu'en local

> Voir la documentation de l'intégration continue pour plus de détail.

## Gestion de la livraison

Quand on parle de livraison il s'agit de la déclaration et la mise à disposition d'une nouvelle version de l'application

### Définition du scope des release

Le scope des versions peut se retrouver dans le CHANGELOG.md à la racine du repository

### Procédure de livraison

Pour livrer il faut :

- Créer une branche de livraison.
- Mettre à jour la version de l'application dans le workflow github default.yml.
- Ouvrir une demande de tirage en direction de la branche main.
- Fusionner la demande de tirage.
- Placer une étiquette sur le nouveau commit

Le commit sur la branche main va engendrer une publication de la nouvelle version.
