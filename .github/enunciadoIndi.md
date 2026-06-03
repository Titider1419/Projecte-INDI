Ghost-in-the-maze
Projecte OpenGL-INDI
Q2 2025-2026

Objectiu
Al llarg d’aquest projecte implementarem un petit joc per guiar el nostre personatge a
través d’un laberint, amb l’objectiu de recollir una sèrie de monedes i arribar a la sortida
sense ser eliminats pel pèrfid fantasma, que ens espera a la foscor.
El projecte es desenvoluparà al llarg del curs, en paral·lel a les sessions de laboratori.
Després de cada sessió es demanarà un petit pas incremental, fins arribar a la compleció
després de l’últim laboratori.
Planificació
1

Increment 1 (3 setmanes) – 23/03/2026
DEFINICIÓ DE L’ESCENA
●  Es proporciona codi per definir un VAO que conté cub de costat 1
ubicat amb el vèrtex mínim a la posició (0,0,0)
●  Carregueu els següents models proporcionats (arxius *.obj):
|     | Alçada original  | Posició del centre de la base de  |     |
| --- | ---------------- | --------------------------------- | --- |
l’objecte
| Morty     | 312.3  |     | (100,  -213,  -6)  |
| --------- | ------ | --- | ------------------ |
| Fantasma  | 0.25   |     | (0, 0, 0)          |
| Moneda    | 11     |     | (0, -5.5, -0.25)   |
| Torre     | 172    |     | (-2, 0, -2)        |

Creeu una funció per cada model (p.ex. modelTransformMorty() )que
crei la TG corresponent per aconseguir un escalat isotròpic (igual en
totes les direccions) de forma que l’alçada a l’escenari sigui:
|     |           | Alçada a l’escena  |     |
| --- | --------- | ------------------ | --- |
|     | Morty     | 1.5                |     |
|     | Fantasma  | 0.65               |     |
|     | Moneda    | 0.5                |     |
|     | Torre     |                    | 6   |
Les funcions modelTransformXXX() hauran de crear i enviar la TG a la
GPU. Així, cal que crideu la funció corresponent abans de pintar cada
model. Més endavant aprofitarem la funció per escalar,  posicionar i
encarar (girar) l’objecte on vulgueu a l’espai de l’escena en un únic
TG.

2

● Definiu una matriu de NxM enters, que representarà un laberint, on:
o 0 són zones transitables.
o 1 són parets : Assegureu que tot el contorn de la matriu són 1
per no deixar sortir el personatge del laberint.
o 2: Punt d’inici, ens indica la posició de sortida del personatge.
(únic al mapa)
o 3: Punt d’inici del fantasma. (únic al mapa)
o 4: indica una sortida del laberint. Poden haver-hi tantes com
vulguem, i ha d’estar necessàriament col·locades al contorn de
la matriu (fila 0 o N-1, o alternativament columna 0 o M-1.
Inicialitzeu la matriu al vostre gust seguint les regles anteriorment
exposades. Les dimensions de la matriu N i M han de ser constants al
codi.
● Dibuixeu l’escena del laberint seguint l’estructura que ens indica la
matriu. A tal efecte, cal que definiu funcions per crear les
transformacions geomètriques de cada element de l’escenari. Podeu
passar a la funció la posició al laberint de l’element concret com a
com a paràmetre.
o Les parets són cubs d’un metre d’aresta, mentre que el terra són
prismes de base quadrada d’un metre de costat i alçada 0,1.
Heu de pintar el laberint de manera que les columnes es dibuixin
en eixos paral·lels a l’eix Z del món i les files cap a les X positives.
o Situeu el personatge i el fantasma a les posicions indicades a la
matriu. Compteu que cada casella mesura 1x1. El personatge
ha de mesurar 1,5 unitats d’alçada i el fantasma 0,65 unitats
d’alçada.
3

o Poseu el model de la torre de sortida al costat de la casella de
sortida, adjacent del laberint. Cal escalar la torre a açada 6 i
rotar la porta per tal que coincideixi amb l’orientació de la
sortida. Dibuixeu bé quina transformació cal fer segons el costat
on estigui la sortida.
● Repartiu inicialment 10 monedes d’alçada 0.5 pel laberint en caselles
aleatòries que siguin terra, sense que se solapin entre elles. Les
monedes han d’estar escalades uniformement sense deformació.
DEFINICIÓ DE LA CÀMERA
● A continuació programarem 2 càmeres per l’escena. La tecla "c"
servirà per alternar entre les vistes, una en perspectiva i l’altre en
ortogonal.
o Una càmera en perspectiva que doni una vista “general”. Es
col·locarà manualment en una coordenada fixa per
aconseguir una vista que mostri un pla picat de 45 graus
aproximadament de tota l’escena. Useu glm::lookAt() per
calcular la VM. Respecte a la matriu de projecció, ajusteu
manualment un valor de FOV per visualitzar tota l’escena.
o Una càmera en perspectiva en vista “primera persona”. La
càmera es col·locarà sobre el cap del personatge, apuntant
cap endavant, amb un FOV de 90 graus. La càmera es mourà
amb el personatge ( i girarà amb ell).
4

IMPORTANT: No hi ha d’haver distorsió quan fem resize de la finestra.
Increment 2 (2 setmanes) – 13/04/2026
CÀLCUL DE CÀMERA
● Assumiu ara que no coneixem la mida dels models (Morty, Fantasma i
moneda). Recorreu els vèrtex dels models per saber-ne la mida i
posició inicial de la seva base (és aconsellable crear una funció a tal
efecte). Adapteu el codi per fer servir aquests valors en la col·locació i
escalat dels models.
● Calcular al codi la capsa contenidora de l'escena en funció de les
dimensions de la matriu N i M.
● Calculeu al codi el centre i el radi de l'escena al codi.
● Calculeu la matriu de projecció per ajustar la zona de visualització a
l'esfera contenidora de l'escena. Feu els càlculs adequats perla vista
general ( en perspectiva ), no cal que modifiqueu la vista en primera
persona.
● Assegureu que al fer resize de la finestra adaptem la matriu de
projecció adequadament de forma que no tallem l'escena ni la
deformem.
● Implementa el gir de les monedes. Al constructor de MyGLWidget
connecteu el signal timeout d’un QTimer a un mètode que podeu
anomenar rotateCoins. Aquest mètode és on heu d’implementar el gir
de les monedes.
MOVIMENT
NOTA: Recordeu que la càmera en primera persona es mourà amb el
personatge ( i girarà amb ell).
● Les tecles del cursor dreta-esquerra permetran girar el personatge
sobre si mateix 90 graus en un o altre sentit.
5

● La tecla del cursor UP farà avançar el personatge endavant, sempre i
quan hi hagi espai lliure.
● Si el personatge passa per una casella on hi ha una moneda, la recull i
incrementa un comptador intern.
● El fantasma es mourà de forma automàtica cada cop que nosaltres
movem el personatge. Per defecte, si no té una paret al davant
avançarà. Ara bé, si es troba en una intersecció o té una paret que
bloqueja, es buscaran totes les caselles buides al seu voltant i es triarà
una de forma aleatòria. Tot seguit, el fantasma girarà vers aquesta
direcció i continuarà avançant.
Increment 3 (1 setmana) – 27/04/2026
● Implementeu a l’escena la visualització amb Euler Angles a la càmera
de vista “general” usant els dos eixos del ratolí.
● Habiliteu el zoom-in / zoom-out clicant el botó dret del mouse alhora
que movem el ratolí en l'eix Y. Alternativament podem usar les tecles
‘+’ i ‘–‘. El zoom pot provocar que l’escena quedi tallada.
● Usarem un segon viewport en miniatura on renderitzarem l’escena
usant una càmera ortogràfica en format “vista aèria”. Col·loqueu la
càmera just a sobre del centre de l’escena, apuntant al centre de
l’escena. Ajusteu la matriu de projecció per a veure tota l’escena.
Aquesta càmera no es veurà afectada per les rotacions d’Euler.
6

Increment 4 (1 setmana) – 4/05/2026
● A l’inici del joc no es permetrà cap moviment del personatge fins que
no es faci “start game” a la UI.
● Quan el joc engegui, mostreu un element d’interfície que indiqui
quantes monedes s’han recollit i el total en format “3/10 coins”, que
indica que s’han recollit 3 de les 10 monedes. Aquest element s’ha
d’actualitzar quan es recull una moneda i quan es fa reset.
● Si el jugador agafa totes les monedes i arriba a una sortida, la UI
indicarà la victòria i no permetrà més moviments fins que no es torni a
fer “Start game”.
● Si el fantasma toca al personatge, s’atura la partida, es mostra un
missatge de “Game Over” i no permetrà més moviments fins que no es
torni a fer “Start game”.
7

● Quan es clica “Start game” cal assegurar-nos que reinicialitzem
l'escena (càmeres, monedes regenerades, posició del personatge i
enemic, etc.)
● Feu també que es pugui moure la càmera en els dos eixos (psi, theta), i
controlar el zoom des de la UI. Cal que els widgets es sincronitzin
adequadament quan movem o fem zoom de l'escena amb el ratolí, i
quan fem servir les tecles de zoom.
● Podrem alternar la càmera de “general” a “primera persona” des de
la UI.
● La rotació de les monedes es podrà engegar/aturar via UI.
Increment 5 (1 setmana) – 11/05/2026
● Implementeu la il·luminació al vertex shader, inicialment useu una llum
d’ambient suau i un focus de llum blanca situat a sobre el centre de
l’escena.
● Amplieu la UI per poder escollir el color del focus principal.
● Canvieu el focus principal de l’escena per tal que sigui un punt mòbil
sobre l'esfera contenidora de l’escena. El punt actuarà com un sol, es
mourà descrivint una trajectòria sobre un meridià, pujant des de
l'equador (θ=0°) cap al pol nord de l'esfera contenidora (θ=90°) , i
baixant per l'altre costat. Useu el pla z=0 per fer el moviment. Controleu
l'angle d'elevació aquest moviment amb les tecles “o” i “p”, i un
control d'usuari adequat.
Increment 6 (1 setmana) – 18/05/2026
● Moveu la il·luminació de l'escena al fragment shader.
● Mitjançant la tecla “N” i un widget adequat, activeu el mode nocturn.
Automàticament el focus principal (sol) s'apagarà i el personatge
encendrà una llanterna groga.
8

● Quan estem en el mode nocturn, el fantasma enemic durà a sobre un
focus de llum que es mourà amb ell.
Increment 7 (1 setmana) – 25/05/2026
● A cadascuna de les monedes de l'escena, afegirem una llum de tipus
focus, apuntant en la direcció de la normal de la cara de la moneda.
La llum rotarà amb la moneda.
Per aconseguir l’efecte de focus d’una forma senzilla només cal
atenuar el càlcul de la llum usant el valor del producte escalar entre la
direcció del focus d i el raig de llum L, limitat dins del rang 0 i 1(els
valors negatius queden a zero). També heu de limitar l’abast de la llum
del focus per tal que no afectin a tota l’escena. Si la distància a la llum
és major a 4 unitats, cal ignorar la llum. Podeu usar una funció
sigmoide amb la distància per per fer-ho de forma suau.
● Utilitzeu la llibreria assimp inclosa en el projecte de mostra i carregueu
el models de la paret i de les torres amb textures. Es proporciona una
textura per la component difusa i una que representa les normals,
ignoreu aquesta última.
9

Increment 8 (1 setmana) – 1/06/2026
● Setmana de buffer.
● EXTRA: utilitzeu la textura de normals per fer un normal-mapping.
10
