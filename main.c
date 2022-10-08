#include <stdio.h> 
#include <stdlib.h>
#include <limits.h> 
#include <stdbool.h>  
#include <time.h>
#define V 81 

const char *cties[81]={"ADANA","ADIYAMAN","AFYONKARAHISAR","AGRI","AMASYA","ANKARA","ANTALYA","ARTVIN","AYDIN","BALIKESIR","BILECIK","BINGOL","BITLIS",
	"BOLU","BURDUR","BURSA","CANAKKALE","CANKIRI","CORUM","DENIZLI","DIYARBAKIR","EDIRNE","ELAZIG","ERZINCAN","ERZURUM","ESKISEHIR","GAZIANTEP","GIRESUN","GUMUSHANE",
	"HAKKARI","HATAY","ISPARTA","MERSIN","ISTANBUL","IZMIR","KARS","KASTAMONU","KAYSERI","KIRKLARELI","KIRSEHIR","KOCAELI","KONYA","KUTAHYA","MALATYA","MANISA",
	"KAHRAMANMARAS","MARDIN","MUGLA","MUS","NEVSEHIR","NIGDE","ORDU","RIZE","SAKARYA","SAMSUN","SIIRT","SINOP","SIVAS","TEKIRDAG","TOKAT","TRABZON","TUNCELI","SANLIURFA",
	"USAK","VAN","YOZGAT","ZONGULDAK","AKSARAY","BAYBURT","KARAMAN","KIRIKKALE","BATMAN","SIRNAK","BARTIN","ARDAHAN","IGDIR","YALOVA","KARABUK","KILIS","OSMANYE","DUZCE"};

int minDistance(int dist[], bool sptSet[]) 
{ 
    int min = INT_MAX, min_index; 
    int v;
    for (v = 0; v < V; v++) 
        if (sptSet[v] == false && dist[v] <= min) 
            min = dist[v], min_index = v; 
    return min_index; 
} 

void printPath(int parent[], int j) 
{ 
    if (parent[j] == - 1) //Base Case
        return; 
    printPath(parent, parent[j]); 
    printf("%s ", cties[j]); 
} 

int printResult(int dist[], int n, int parent[],int src) 
{ 
    printf("Source \t Destination \t\t Distance(Km) \t Route"); 
    printf("\n----------------------------------------------------------------------------------------------------------------------------------"); 
    int i;
	for (i = 1; i < V; i++) 
    { 
        printf("\n%s -> %-20s \t %6d Km \t%s ", 
                      cties[src], cties[i], dist[i], cties[src]); 
        printPath(parent, i); 
    } 
} 
  
void DijkstraFunction(int graph[V][V], int src) 
{ 
    int dist[V]; 
    bool sptSet[V];
    int parent[V]; 
    int i;
	for (i = 0; i < V; i++) 
    { 
        parent[i] = -1; 
        dist[i] = INT_MAX; 
        sptSet[i] = false; 
    } 
    dist[src] = 0; 
    int count;
	for (count = 0; count < V - 1; count++) 
    { 
        int u = minDistance(dist, sptSet); 
        sptSet[u] = true; 
        int v;
		for (v = 0; v < V; v++) 
        {
            if (!sptSet[v] && graph[u][v] && 
                dist[u] + graph[u][v] < dist[v]) 
            { 
                parent[v] = u; 
                dist[v] = dist[u] + graph[u][v]; 
            }  
		}
    } 
    printResult(dist, V, parent,src); 
} 

void Loadmatrix(int graph[V][V]) 
{
	 int i,j;
	 FILE *myFile;
 	 myFile = fopen("81citiesmatrix.txt", "r");
 	 for (i = 0; i < V; i++)
 	 {
	  	for (j = 0; j < V; j++)
 		{
 			fscanf(myFile, "%d", &graph[i][j]);
 		}
 	}
 	fclose(myFile);
}
  
int main() 
{ 
  int graph[V][V];
  Loadmatrix(graph);
  clock_t start,stop;
  int citynumber;
  system("CLS");
  printf("Please Enter the License Plate Code of Your Starting City (1-81): ");
  scanf("%d",&citynumber);
  if (citynumber<1 || citynumber>81)
  {
  	printf("You Entered Incorrect License Plate Code !!!");
  	exit(0);
  }
  citynumber--;
  system("CLS");
  start = clock();
  DijkstraFunction(graph, citynumber); 
  stop = clock();
  double time_taken = (double)(stop-start)/CLOCKS_PER_SEC; //seconds
  printf("\nAlgorithm Completion Time: %2.10f Sec.\n",time_taken); 
  return 0; 
} 
