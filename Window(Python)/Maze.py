import pygame
import random

import time
import sys

class maze:
    def __init__(self):
        self.cell = 0
        self.size = 0
        self.grid = []
        self.edges = []
        self.weight = []
        self.adjMat = []
        self.pathway = []
        self.adjlist = []
        pygame.init()
        self.res = (1920,1080)
        self.screen = pygame.display.set_mode(self.res)
        self.color = (255,255,255)
        self.color_size = (102,51,153)
        self.font = pygame.font.SysFont('dejavuserif',60)
        self.sizeButton_builder()

  

    def sizeButton_builder(self):
        qui = self.font.render('QUIT' , True , self.color)
        five = self.font.render('5' , True , self.color)
        ten = self.font.render('10' , True , self.color)
        twenty = self.font.render('20' , True , self.color)
        fifty = self.font.render('50' , True , self.color)

        
        self.screen.fill((0,0,0))

        pygame.draw.rect(self.screen, self.color_size, [1550, 225, 300,100])
        pygame.draw.rect(self.screen, self.color_size, [1550, 400, 300,100])
        pygame.draw.rect(self.screen, self.color_size, [1550, 575, 300,100])
        pygame.draw.rect(self.screen, self.color_size, [1550, 750, 300,100])

        pygame.draw.rect(self.screen, (255,0,0),[1230,50, 440,100])
                
            
            
            # superimposing the text onto our button
        self.screen.blit(qui, (1370,65))
        self.screen.blit(five, (1690, 240))
        self.screen.blit(ten, (1670, 420))
        self.screen.blit(twenty, (1670, 590))
        self.screen.blit(fifty, (1670, 770))


        pygame.display.update()
        notclicked = True
        while notclicked:
            mouse = pygame.mouse.get_pos()
            for ev in pygame.event.get():

                if ev.type == pygame.MOUSEBUTTONDOWN:

                    if 1230 <= mouse[0] <= 1670 and 50 <= mouse[1] <= 150:
                        pygame.quit()
                    if 1550 <= mouse[0] <= 1850:
                        if 225 <= mouse[1] <= 325:
                            self.size = 50
                            self.cell = 1000/(self.size/10)
                            notclicked = False
                        if 400 <= mouse[1] <= 500:
                            self.size = 100
                            self.cell = 1000/(self.size/10)
                            notclicked = False
                        if 575 <= mouse[1] <= 675:
                            self.size = 200
                            self.cell = 1000/(self.size/10)
                            notclicked = False
                        if 750 <= mouse[1] <= 850:
                            self.size = 500
                            self.cell = 1000/(self.size/10)
                            notclicked = False
        self.build_grid()
        
    
    def build_grid(self):
        for i in range(0,1001):
            tmp = []
            for j in range(0, 1001):
                if(i %self.cell ==0 or j % self.cell == 0):
                    tmp.append(1)
                    self.screen.set_at((i, j), (255,255,255))
                else:
                    tmp.append(0)
            self.grid.append(tmp)
        pygame.display.update()
        
        
        for i in range(0,1001):
            tmp = []
            for j in range(0, 1001):
                if(i < self.cell and j < self.cell and self.grid[i][j] != 1):
                    self.screen.set_at((i, j), (0,255,0))
                if(i > 1000-self.cell and j > 1000-self.cell and self.grid[i][j] !=1 and i < 1000 and j < 1000):
                    self.screen.set_at((i, j), (255,0,0))
                if(i %(self.cell/2) == 0 and j % (self.cell/2) == 0 and self.grid[i][j] !=1):
                    tmp.append(random.randint(1,20))
                    pair = [i,j]
                    self.edges.append(pair)
            if(len(tmp) !=0):
                self.weight.append(tmp)
        pygame.display.update()
        self.adjMat_builder()
    
    def adjMat_builder(self):
        maxsize = len(self.weight) * len(self.weight)
        n = len(self.weight)
        for i in range(0, maxsize):
            tmp= []
            tmp2 = []
            for j in range(0, maxsize):
                check =0
                if(i >= n):
                    if(j == i -n):
                        check =1
                        row = j/n
                        col = j%n
                        tmp.append(self.weight[int(row)][int(col)])
                        tmp2.append(j)
                
                if(i < maxsize - n):
                    if(j == i+n):
                        check = 1
                        row = j/n
                        col = j%n
                        tmp.append(self.weight[int(row)][int(col)])
                        tmp2.append(j)
                
                if((i+1)%n !=0):
                    if(j == i+1):
                        check =1 
                        row = j/n
                        col = j%n
                        tmp.append(self.weight[int(row)][int(col)])
                        tmp2.append(j)

                if((i+1)%n !=1):
                    if(j == i-1):
                        check =1
                        row = j/n
                        col = j%n
                        tmp.append(self.weight[int(row)][int(col)])
                        tmp2.append(j)
                
                if(check == 0):
                    tmp.append(1000)
                    
            self.adjMat.append(tmp)
            self.adjlist.append(tmp2)
        
        self.rand_prims()
        
    def rand_prims(self):
        vert = len(self.adjMat)
        newGraph = [0]*vert
        key = [1000]*vert
        visited = [False]*vert
        key[0] = 0
        newGraph[0] = -1
        for i in range(0,(vert-1)):
            min = 10000
            index =0
            for j in range(0, vert):
                if(visited[j] == False and key[j] < min):
                    min = key[j]
                    index = j
            
            visited[index] = True
            for j in range(0, len(self.adjlist[index])):
                if(self.adjMat[index][self.adjlist[index][j]] and visited[self.adjlist[index][j]] ==False and self.adjMat[index][self.adjlist[index][j]]< key[self.adjlist[index][j]]):
                    
                    
                    newGraph[self.adjlist[index][j]] = index
                    key[self.adjlist[index][j]] = self.adjMat[index][self.adjlist[index][j]]
            
        self.gen_maze(newGraph)
    
    def gen_maze(self, mazelayout = [], ):
        vert = len(self.adjMat)
        for i in range(1, vert):
            a =i
            b = mazelayout[i]
            self.adjMat[a][b] = 50
            self.adjMat[b][a] = 50
            
            if(a>b):
                tmp = b
                b= a
                a = tmp
            
            if(a+1 == b):
                j = self.edges[a][1]+(self.cell/2)
                k = self.edges[a][0]-(self.cell/2)+1
                pygame.draw.aaline(self.screen, (0,0,0), (j,k), (j, k+self.cell-1), 1 )
                
                for l in range(0, int(self.cell-1)):
                    self.grid[int(j)][int(k+l)] = 0
                
            
            
            elif(a+(self.size/10) == b):
                j = self.edges[a][1]-(self.cell/2)+1
                k = self.edges[a][0]+(self.cell/2)
                pygame.draw.aaline(self.screen, (0,0,0), (j,k), (j+self.cell-1, k), 1 )
              
                for l in range(0, int(self.cell-1)):
                    #self.screen.set_at((int(j+l), int(k)), (0,0,0))
                    
                    self.grid[int(j+l)][int(k)] = 0

        pygame.display.update()
        


        bfs = self.font.render('BFS', True, self.color)
        pygame.draw.rect(self.screen, (0,0,255), [1100, 225, 300,100])
        self.screen.blit(bfs, (1180,240))
        dfs = self.font.render('DFS', True, self.color)
        pygame.draw.rect(self.screen, (0,0,255), [1100, 400, 300,100])
        self.screen.blit(dfs, (1180,420))
        font2 = pygame.font.SysFont('dejavuserif',55)
        di = font2.render('DIJKSTRA', True, self.color)
        pygame.draw.rect(self.screen, (0,0,255), [1100, 575, 300,100])
        self.screen.blit(di, (1105,590))
        pygame.display.update()

        for i in range(0, vert):
            for j in range(0,vert):
                if(self.adjMat[i][j] != 50):
                    self.adjMat[i][j] =0
                else:
                    self.adjMat[i][j] =1
        
        
        notclicked = True
        while notclicked:
            mouse = pygame.mouse.get_pos()
            for ev in pygame.event.get():

                if ev.type == pygame.MOUSEBUTTONDOWN:

                    if 1230 <= mouse[0] <= 1670 and 50 <= mouse[1] <= 150:
                        pygame.quit()
                    if 1550 <= mouse[0] <= 1850:
                        if 225 <= mouse[1] <= 325:
                            self.size = 50
                            self.cell = 1000/(self.size/10)
                            notclicked = False
                            self.repeat()
                        if 400 <= mouse[1] <= 500:
                            self.size = 100
                            self.cell = 1000/(self.size/10)
                            notclicked = False
                            self.repeat()
                        if 575 <= mouse[1] <= 675:
                            self.size = 200
                            self.cell = 1000/(self.size/10)
                            notclicked = False
                            self.repeat()
                        if 750 <= mouse[1] <= 850:
                            self.size = 500
                            self.cell = 1000/(self.size/10)
                            notclicked = False
                            self.repeat()

                    if(1100 <= mouse[0] <= 1400):
                        if(225 <= mouse[1] <= 325):
                            #bfs
                            notclicked = False
                            self.pathway = [-1]*vert
                            self.BFS()
                            self.pathway.clear()
                            self.decide()
                            
                        if(400 <= mouse[1] <= 500):
                            notclicked = False
                            visited = [False]*vert
                            self.pathway.append(0)
                            self.DFS(0, visited)
                            for k in range(0, len(self.pathway)):
                                a = self.edges[self.pathway[k]][1]
                                b = self.edges[self.pathway[k]][0]
                                a = a-(self.cell/2)
                                b = b-(self.cell/2)
                                
                                for l in range(0, int(self.cell)):
                                    for m in range(0, int(self.cell)):
                                        if((self.grid[int(a+l)][int(b+m)]) != 1):
                                            self.screen.set_at((int(a+l), int(b+m)), (48,255,96))
                                pygame.display.update()
                            visited.clear()
                            self.pathway.clear()
                            self.decide()
                        if(575 <= mouse[1] <= 675):
                            notclicked = False
                            self.Dijkstra()
                            self.pathway.clear()
                            self.decide()
                            
    def decide(self):
        notclicked = True
        while notclicked:
            mouse = pygame.mouse.get_pos()
            for ev in pygame.event.get():

                if ev.type == pygame.MOUSEBUTTONDOWN:

                    if 1230 <= mouse[0] <= 1670 and 50 <= mouse[1] <= 150:
                        pygame.quit()
                    if 1550 <= mouse[0] <= 1850:
                        if 225 <= mouse[1] <= 325:
                            self.size = 50
                            self.cell = 1000/(self.size/10)
                            notclicked = False
                            self.repeat()
                        if 400 <= mouse[1] <= 500:
                            self.size = 100
                            self.cell = 1000/(self.size/10)
                            notclicked = False
                            self.repeat()
                        if 575 <= mouse[1] <= 675:
                            self.size = 200
                            self.cell = 1000/(self.size/10)
                            notclicked = False
                            self.repeat()
                        if 750 <= mouse[1] <= 850:
                            self.size = 500
                            self.cell = 1000/(self.size/10)
                            notclicked = False
                            self.repeat()


                    if(1100 <= mouse[0] <= 1400):
                        if(225 <= mouse[1] <= 325):
                            #bfs
                            notclicked = False
                            self.maze_reset()
                            self.pathway = [-1]*len(self.adjMat)
                            self.BFS()
                            self.pathway.clear()
                            self.decide()
                            
                            
                            x=5
                        if(400 <= mouse[1] <= 500):
                            notclicked = False
                            self.maze_reset()
                            visited = [False]*len(self.adjMat)
                            self.pathway.append(0)
                            self.DFS(0, visited)
                            
                            for k in range(0, len(self.pathway)):
                                a = self.edges[self.pathway[k]][1]
                                b = self.edges[self.pathway[k]][0]
                                a = a-(self.cell/2)
                                b = b-(self.cell/2)
                                
                                for l in range(0, int(self.cell)):
                                    for m in range(0, int(self.cell)):
                                        if((self.grid[int(a+l)][int(b+m)]) != 1):
                                            self.screen.set_at((int(a+l), int(b+m)), (48,255,96))
                                pygame.display.update()
                            visited.clear()
                            self.pathway.clear()
                            self.decide()
                        if(575 <= mouse[1] <= 675):
                            notclicked = False
                            self.maze_reset()
                            self.Dijkstra()
                            self.pathway.clear()
                            self.decide()
    def repeat(self):
        self.grid.clear()
        self.edges.clear()
        self.adjMat.clear()
        self.weight.clear()
        self.pathway.clear()
        self.adjlist.clear()
        self.blackWindow()
        self.build_grid()
    
    def maze_reset(self):
        for i in range(0,1001):
            for j in range(0,1001):
                if(self.grid[i][j] !=1 ):
                    self.screen.set_at((int(i), int(j)), (0,0,0))
        pygame.display.update()
    def blackWindow(self):
        for i in range(0,1050):
            for j in range(0,1080):
                self.screen.set_at((int(i), int(j)), (0,0,0))
        pygame.display.update()
            
    def BFS(self):
        q = []
        visited = [False]*len(self.adjMat)
        self.pathway[0] = -1
        q.append(0)
        visited[0] = True
        while(len(q) != 0 ):
            u = q.pop(0)
            if(u == len(self.adjMat)-1):
                self.printPath(len(self.adjMat)-1)
                return
            a = self.edges[u][1]
            b = self.edges[u][0]
            a = a-(self.cell/2)
            b = b-(self.cell/2)
            
            for i in range(0, int(self.cell)):
                for j in range(0, int(self.cell)):
                    if((self.grid[int(a+i)][int(b+j)]) != 1):
                        self.screen.set_at((int(a+i), int(b+j)), (100,100,100))
            pygame.display.update()
            time.sleep(5/10000000000)
            
            
            
            for i in range(0,len(self.adjMat)):
                if(self.adjMat[u][i] == 1 and visited[i] == False):
                    q.append(i)
                    self.pathway[i] = u
                    visited[i] = True
        
    
    def printPath(self, current):
        if(current == -1):
            return

        self.printPath(self.pathway[current])
        a = self.edges[current][1]
        b = self.edges[current][0]
        a = a-(self.cell/2)
        b = b-(self.cell/2)
        for i in range(0, int(self.cell)):
                for j in range(0, int(self.cell)):
                    if((self.grid[int(a+i)][int(b+j)]) != 1):
                        self.screen.set_at((int(a+i), int(b+j)), (48,255,96))
        pygame.display.update()
        time.sleep(5/10000000000)
        return
    
    def DFS(self, start, visited = []):
        check = 0
        if(start == len(self.adjMat)-1):
            self.pathway.append(start)
            return -1
        
        a = self.edges[start][1]
        b = self.edges[start][0]
        a = a-(self.cell/2)
        b = b-(self.cell/2)
        for i in range(0, int(self.cell)):
                for j in range(0, int(self.cell)):
                    if((self.grid[int(a+i)][int(b+j)]) != 1):
                        self.screen.set_at((int(a+i), int(b+j)), (100,100,100))
        visited[start] = True
        pygame.display.update()
        
        for i in range(0, len(self.adjMat)):
            if(self.adjMat[start][i] ==1 and visited[i] == False):
                check = self.DFS(i, visited)
                if(check == -1):
                    self.pathway.append(i)
                    return -1
    
    def Dijkstra(self):
        n = len(self.adjMat)
        self.pathway = [-1]*n
        v = [False]*n
        d = [9999]*n
        q = []
        q.append(0)
        d[0] = 0
        while(len(q)!= 0):
            vis = q.pop(0)
            a = self.edges[vis][1]
            b = self.edges[vis][0]
            a = a-(self.cell/2)
            b = b-(self.cell/2)
            for i in range(0, int(self.cell)):
                    for j in range(0, int(self.cell)):
                        if((self.grid[int(a+i)][int(b+j)]) != 1):
                            self.screen.set_at((int(a+i), int(b+j)), (100,100,100))
            pygame.display.update()
            
            nearest = -1
            shortestdis = 9999
            
            for i in range(0,n):
                if v[i] == False and d[i] < shortestdis:
                    nearest = i
                    shortestdis = d[i]
            
            for i in range(0,n):
                total = self.adjMat[vis][i] +shortestdis
                if(self.adjMat[vis][i] == 1 and total < d[i]):
                    self.pathway[i] = vis
                    d[i] = total
                    v[i] = True
                    if(i == n-1):
                        self.printPath(n-1)
                        return 0
                    q.append(i)
            
m = maze()
    





                  
    
      

    
      

    