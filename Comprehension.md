Fichier pour la comprehension du sujet via les fonctions principal autoriser

Fonction pour la Creation de notre Serveur IRC:

1. La fonction socket():
int socket(int domain, int type, int protocol);

Utilisée pour créer un point de communication appelé "socket" qui permet à un programme de communiquer avec d'autres programmes via un réseau, qu'il soit local ou distant.
Elle retourne un fd ou -1 en cas de probleme.
Une fois la socket créée, elle peut être configurée pour écouter des connexions entrantes, se connecter à une autre socket, envoyer et recevoir des données, etc.
Il est important de fermer la socket avec la fonction close une fois qu'elle n'est plus nécessaire pour libérer les ressources.

domain: domaine de communication, AF_INET pour IPv4, AF_INET6 pour IPv6 et AF_UNIX pour la communication local ----> Pour ce projet nous utiliseront AF_INET

type: indique le type de socket a creer, SOCK_STREAM pour les connexions orientées (TCP), SOCK_DGRAM pour les connexions sans connexion (UDP) ----> Pour ce projet nous utiliseront SOCK_STREAM

protocol: Spécifie le protocole à utiliser avec le type de socket ----> Set a 0 pour ce projet c'est le protocol par default pour la plupart des usages

2. La fonction setsockopt();
int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);

sockfd: Le descripteur de la socket sur laquelle l'option doit être définie.
Elle retourne 0 en cas de success ou -1 en cas de probleme.

level: Le niveau auquel l'option est définie. Les niveaux courants sont :
                                                                SOL_SOCKET : Pour les options génériques de la socket
                                                                IPPROTO_TCP : Pour les options spécifiques au protocole TCP
                                                                IPPROTO_IP : Pour les options spécifiques au protocole IP

optname: Le nom de l'option à définir. Voici quelques options courantes :
                                                                SO_REUSEADDR : Pour permettre la réutilisation de l'adresse locale -------------------------------------------> Ce que l'on utilise pour le projet.
                                                                SO_KEEPALIVE : Pour maintenir les connexions TCP actives en envoyant périodiquement des messages
                                                                SO_RCVBUF : Pour définir la taille du tampon de réception
                                                                SO_SNDBUF : Pour définir la taille du tampon d'envoi

optval: Un pointeur vers la valeur de l'option à définir.

optlen: La taille de la valeur de l'option en octets

3. La fonction fcntl():
int fcntl(int fd, int cmd, ... /* arg */ );

Utilisée pour manipuler les descripteurs de fichier. Elle permet de contrôler différents aspects des descripteurs de fichier.
Elle retourne 0 en cas de success ou -1 en cas de probleme.

fd: Le descripteur de fichier à manipuler. ---> celui de notre socket.

cmd: La commande à exécuter. Les commandes courantes incluent :
                                                    F_GETFL : Obtenir les indicateurs du descripteur de fichier.
                                                    F_SETFL : Définir les indicateurs du descripteur de fichier. -------------------------------------> Ce que l'on utilise
                                                    F_GETFD : Obtenir les flags du descripteur de fichier (par exemple, close-on-exec).
                                                    F_SETFD : Définir les flags du descripteur de fichier.
                                                    F_GETLK, F_SETLK, F_SETLKW : Obtenir ou définir un verrou sur une section du fichier.

arg: Un argument additionnel facultatif, requis par certaines commandes. Le type et la signification de cet argument varient en fonction de la commande. -----> Nous utilisons O_NONBLOCK afin de rendre notre fd non-blocant

4. la fonction bind():
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

Utilisée pour attacher une adresse locale (nommée "adresse socket") à une socket.
Cela est principalement nécessaire pour les sockets de serveur qui doivent être liées à une adresse et à un port spécifique pour accepter les connexions entrantes.
La fonction bind est une étape essentielle dans la configuration des sockets de serveur, permettant à une application de spécifier sur quelle adresse et quel port elle doit écouter les connexions entrantes.
Elle retourne 0 en cas de success ou -1 en cas de probleme.

sockfd: Le descripteur de fichier de la socket à laquelle l'adresse sera liée. Cette socket doit avoir été créée préalablement avec la fonction socket.

addr: Un pointeur vers une structure sockaddr qui contient l'adresse locale à attacher à la socket. La structure exacte dépend de la famille d'adresses (par exemple, struct sockaddr_in pour IPv4, struct sockaddr_in6 pour IPv6).

addrlen: La taille de la structure pointée par addr.

5. la fonction listen():
int listen(int sockfd, int backlog);

Utilisée pour marquer une socket comme étant une socket passive, c'est-à-dire une socket qui sera utilisée pour accepter des connexions entrantes.
Elle retourne 0 en cas de success ou -1 en cas de probleme.

sockfd: Le descripteur de fichier de la socket à marquer comme passive. Cette socket doit avoir été créée avec la fonction socket et liée à une adresse locale avec la fonction bind.

backlog: Le nombre maximum de connexions en attente qui peuvent être maintenues dans la file d'attente des connexions incomplètes. ----> On utilise la macro SOMAXCONN qui est egale au noombre maximal que peut acceuillir notre systeme
Si la file d'attente est pleine, les nouvelles demandes de connexion peuvent être rejetées

