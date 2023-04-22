#include <include/game.hpp>
vector<vector<int>> puzzle;
int grid_size[2];
SDL_Surface *grid_surf;
SDL_Rect grid_rect;
SDL_Rect dstgrid;
vector<vector<int>> dark_squares;
vector<vector<int>> circled_squares;
Image box;
Image darkbox;
Image circle;
Image grid_image;
Text grid_text;
int main( int argc, char* args[] ) {
    initiliaze();
    grid_text.init("times-new-roman.ttf", 20);
    puzzle = {{5, 5, 5, 6, 5, 2, 7, 3},
              {5, 6, 2, 9, 8, 3, 7, 1},
              {4, 4, 1, 6, 6, 4, 9, 7},
              {1, 7, 4, 8, 8, 6, 1, 9},
              {3, 5, 5, 2, 4, 9, 1, 8},
              {5, 3, 2, 1, 3, 4, 7, 5},
              {6, 8, 3, 5, 2, 7, 4, 6},
              {1, 1, 1, 3, 8, 5, 8, 2}};
    grid_size[0] = 8;
    grid_size[1] = 8;
    dark_squares = {};
    circled_squares = {};
    grid_surf = SDL_CreateRGBSurface(0,grid_size[0]*64,grid_size[1]*64,32,0,0,0,SDL_ALPHA_OPAQUE);
    grid_rect.w = 64;
    grid_rect.h = 64;
    grid_rect.x = 0;
    grid_rect.y = 0;
    int pos[2] = {0, 0};
    int pos_[2] = {0, 0};
    box.init(IMG_Load("box.png"));
    circle.init(IMG_Load("circle.png"), white);
    darkbox.init(IMG_Load("dark_box.png"), red);
    string num;
    for(int j = 0; j < grid_size[1]; j=j+1){
        for(int i = 0; i < grid_size[0]; i=i+1){
            if (i<=(grid_size[0]-3)){
                if (puzzle[j][i]==puzzle[j][i+1] && puzzle[j][i]==puzzle[j][i+2]){
                    vector<int> pos = {i, j};
                    vector<int> pos2 = {i+2, j};
                    vector<int> pos3 = {i+1, j};
                    dark_squares.push_back(pos);
                    dark_squares.push_back(pos2);
                    circled_squares.push_back(pos3);
                    if (i>0){
                        vector<int> pos4 = {i-1, j};
                        circled_squares.push_back(pos4);
                    }
                    if ((i+3)<grid_size[0]){
                        vector<int> pos5 = {i+3, j};
                        circled_squares.push_back(pos5);
                    }
                    if ((j+1)<grid_size[1]){
                        vector<int> pos6 = {i, j+1};
                        vector<int> pos7 = {i+2, j+1};
                        circled_squares.push_back(pos6);
                        circled_squares.push_back(pos7);
                    }
                    if ((j-1)>=0){
                        vector<int> pos8 = {i, j-1};
                        vector<int> pos9 = {i+2, j-1};
                        circled_squares.push_back(pos8);
                        circled_squares.push_back(pos9);
                    }
                }
                if (puzzle[j][i]==puzzle[j][i+2] && puzzle[j][i]!=puzzle[j][i+1]){
                    vector<int> pos10 = {i+1, j};
                    circled_squares.push_back(pos10);
                }
            }
            
        }
    }
    for(int i = 0; i < grid_size[0]; i=i+1){
        for(int j = 0; j < grid_size[1]; j=j+1){
            if (j<=(grid_size[1]-3)){
                if (puzzle[j][i]==puzzle[j+1][i] && puzzle[j][i]==puzzle[j+2][i]){
                    vector<int> pos = {i, j};
                    vector<int> pos2 = {i, j+2};
                    vector<int> pos3 = {i, j+1};
                    dark_squares.push_back(pos);
                    dark_squares.push_back(pos2);
                    circled_squares.push_back(pos3);
                    if (j>0){
                        vector<int> pos4 = {i, j-1};
                        circled_squares.push_back(pos4);
                    }
                    if ((j+3)<grid_size[1]){
                        vector<int> pos5 = {i, j+3};
                        circled_squares.push_back(pos5);
                    }
                    if ((i+1)<grid_size[0]){
                        vector<int> pos6 = {i+1, j};
                        vector<int> pos7 = {i+1, j+2};
                        circled_squares.push_back(pos6);
                        circled_squares.push_back(pos7);
                    }
                    if ((i-1)>=0){
                        vector<int> pos8 = {i-1, j};
                        vector<int> pos9 = {i-1, j+2};
                        circled_squares.push_back(pos8);
                        circled_squares.push_back(pos9);
                    }
                }
                if (puzzle[j][i]==puzzle[j+2][i] && puzzle[j][i]!=puzzle[j+1][i]){
                    vector<int> pos10 = {i, j+1};
                    circled_squares.push_back(pos10);
                }
            }
        }
    }
    bool t1 = false;
    bool t2 = false;
    for (int num = 0; num < 5; num=num+1){
        for(int j = 0; j < grid_size[1]; j=j+1){
            for(int i = 0; i < grid_size[0]; i=i+1){
                for(int jx = 0; jx < grid_size[1]; jx=jx+1){
                    if (puzzle[j][i]==puzzle[jx][i] && j!=jx){
                        for (int l = 0; l < circled_squares.size(); l = l+1){
                            if (circled_squares[l][0]==i && circled_squares[l][1] == jx){
                                vector<int> pos = {i, j};
                                dark_squares.push_back(pos);
                                break;
                            }
                        }
                    }
                }
            }
        }
        for(int i = 0; i < grid_size[0]; i=i+1){
            for(int j = 0; j < grid_size[1]; j=j+1){
                for(int ix = 0; ix < grid_size[1]; ix=ix+1){
                    if (puzzle[j][i]==puzzle[j][ix] && i!=ix){
                        for (int l = 0; l < circled_squares.size(); l = l+1){
                            if (circled_squares[l][0]==ix && circled_squares[l][1] == j){
                                vector<int> pos = {i, j};
                                dark_squares.push_back(pos);
                                break;
                            }
                        }
                    }
                }
            }
        }
        for(int i = 0; i < grid_size[0]; i=i+1){
            for(int j = 0; j < grid_size[1]; j=j+1){
                if (i==0){
                    t1 = false;
                    t2 = false;
                    vector<int> pos2 = {i+1, j+1};
                    vector<int> pos3 = {i, j+2};
                    vector<int> pos4 = {i-1, j-1};
                    vector<int> pos5 = {i, j-2};
                    for (int l = 0; l < dark_squares.size(); l = l+1){
                        if (dark_squares[l][0]==pos2[0] && dark_squares[l][1]==pos2[1]){
                            t1= true;
                        }
                    }
                    for (int lx = 0; lx < dark_squares.size(); lx = lx+1){
                        if (dark_squares[lx][0]==pos3[0] && dark_squares[lx][1]==pos3[1]){
                            t2=true;
                        }
                    }
                    if (!(t1 or t2)){
                        for (int l = 0; l < dark_squares.size(); l = l+1){
                            if (dark_squares[l][0]==pos4[0] && dark_squares[l][1]==pos4[1]){
                                t1= true;
                            }
                        }
                        for (int lx = 0; lx < dark_squares.size(); lx = lx+1){
                            if (dark_squares[lx][0]==pos5[0] && dark_squares[lx][1]==pos5[1]){
                                t2=true;
                            }
                        }
                    }
                    if (t1&&t2){
                        vector<int> pos = {i, j};
                        circled_squares.push_back(pos);
                    }
                }
                if (i==grid_size[1]-1){
                    t1 = false;
                    t2 = false;
                    vector<int> pos2 = {i-1, j+1};
                    vector<int> pos3 = {i, j+2};
                    vector<int> pos4 = {i-1, j-1};
                    vector<int> pos5 = {i, j-2};
                    for (int l = 0; l < dark_squares.size(); l = l+1){
                        if (dark_squares[l][0]==pos2[0] && dark_squares[l][1]==pos2[1]){
                            t1= true;
                        }
                    }
                    for (int lx = 0; lx < dark_squares.size(); lx = lx+1){
                        if (dark_squares[lx][0]==pos3[0] && dark_squares[lx][1]==pos3[1]){
                            t2=true;
                        }
                    }
                    if (!(t1 or t2)){
                        for (int l = 0; l < dark_squares.size(); l = l+1){
                            if (dark_squares[l][0]==pos4[0] && dark_squares[l][1]==pos4[1]){
                                t1= true;
                            }
                        }
                        for (int lx = 0; lx < dark_squares.size(); lx = lx+1){
                            if (dark_squares[lx][0]==pos5[0] && dark_squares[lx][1]==pos5[1]){
                                t2=true;
                            }
                        }
                    }
                    if (t1&&t2){
                        vector<int> pos = {i, j};
                        circled_squares.push_back(pos);
                    }
                }
                if (j==0){
                    t1 = false;
                    t2 = false;
                    vector<int> pos2 = {i-2, j};
                    vector<int> pos3 = {i-1, j+1};
                    vector<int> pos4 = {i+2, j};
                    vector<int> pos5 = {i+1, j+1};
                    for (int l = 0; l < dark_squares.size(); l = l+1){
                        if (dark_squares[l][0]==pos2[0] && dark_squares[l][1]==pos2[1]){
                            t1= true;
                        }
                    }
                    for (int lx = 0; lx < dark_squares.size(); lx = lx+1){
                        if (dark_squares[lx][0]==pos3[0] && dark_squares[lx][1]==pos3[1]){
                            t2=true;
                        }
                    }
                    if (!(t1 or t2)){
                        for (int l = 0; l < dark_squares.size(); l = l+1){
                            if (dark_squares[l][0]==pos4[0] && dark_squares[l][1]==pos4[1]){
                                t1= true;
                            }
                        }
                        for (int lx = 0; lx < dark_squares.size(); lx = lx+1){
                            if (dark_squares[lx][0]==pos5[0] && dark_squares[lx][1]==pos5[1]){
                                t2=true;
                            }
                        }
                    }
                    if (t1&&t2){
                        vector<int> pos = {i, j};
                        circled_squares.push_back(pos);
                    }
                }
                if (j==grid_size[1]-1){
                    t1 = false;
                    t2 = false;
                    vector<int> pos2 = {i-2, j};
                    vector<int> pos3 = {i-1, j-1};
                    vector<int> pos4 = {i+2, j};
                    vector<int> pos5 = {i+1, j-1};
                    for (int l = 0; l < dark_squares.size(); l = l+1){
                        if (dark_squares[l][0]==pos2[0] && dark_squares[l][1]==pos2[1]){
                            t1= true;
                        }
                    }
                    for (int lx = 0; lx < dark_squares.size(); lx = lx+1){
                        if (dark_squares[lx][0]==pos3[0] && dark_squares[lx][1]==pos3[1]){
                            t2=true;
                        }
                    }
                    if (!(t1 or t2)){
                        for (int l = 0; l < dark_squares.size(); l = l+1){
                            if (dark_squares[l][0]==pos4[0] && dark_squares[l][1]==pos4[1]){
                                t1= true;
                            }
                        }
                        for (int lx = 0; lx < dark_squares.size(); lx = lx+1){
                            if (dark_squares[lx][0]==pos5[0] && dark_squares[lx][1]==pos5[1]){
                                t2=true;
                            }
                        }
                    }
                    if (t1&&t2){
                        vector<int> pos = {i, j};
                        circled_squares.push_back(pos);
                    }
                }
                if (i==1){
                    t1 = false;
                    t2 = false;
                    vector<int> pos2 = {i-1, j-1};
                    vector<int> pos3 = {i-1, j+1};
                    for (int l = 0; l < dark_squares.size(); l = l+1){
                        if (dark_squares[l][0]==pos2[0] && dark_squares[l][1]==pos2[1]){
                            t1= true;
                        }
                    }
                    for (int lx = 0; lx < dark_squares.size(); lx = lx+1){
                        if (dark_squares[lx][0]==pos3[0] && dark_squares[lx][1]==pos3[1]){
                            t2=true;
                        }
                    }
                    if (t1&&t2){
                        vector<int> pos = {i, j};
                        circled_squares.push_back(pos);
                    }
                }
                if (j==1){
                    t1 = false;
                    t2 = false;
                    vector<int> pos2 = {i-1, j-1};
                    vector<int> pos3 = {i+1, j-1};
                    for (int l = 0; l < dark_squares.size(); l = l+1){
                        if (dark_squares[l][0]==pos2[0] && dark_squares[l][1]==pos2[1]){
                            t1= true;
                        }
                    }
                    for (int lx = 0; lx < dark_squares.size(); lx = lx+1){
                        if (dark_squares[lx][0]==pos3[0] && dark_squares[lx][1]==pos3[1]){
                            t2=true;
                        }
                    }
                    if (t1&&t2){
                        vector<int> pos = {i, j};
                        circled_squares.push_back(pos);
                    }
                }
                if (i==grid_size[0]-2){
                    t1 = false;
                    t2 = false;
                    vector<int> pos2 = {i+1, j-1};
                    vector<int> pos3 = {i+1, j+1};
                    for (int l = 0; l < dark_squares.size(); l = l+1){
                        if (dark_squares[l][0]==pos2[0] && dark_squares[l][1]==pos2[1]){
                            t1= true;
                        }
                    }
                    for (int lx = 0; lx < dark_squares.size(); lx = lx+1){
                        if (dark_squares[lx][0]==pos3[0] && dark_squares[lx][1]==pos3[1]){
                            t2=true;
                        }
                    }
                    if (t1&&t2){
                        vector<int> pos = {i, j};
                        circled_squares.push_back(pos);
                    }
                }
                if (j==grid_size[1]-2){
                    t1 = false;
                    t2 = false;
                    vector<int> pos2 = {i-1, j+1};
                    vector<int> pos3 = {i+1, j+1};
                    for (int l = 0; l < dark_squares.size(); l = l+1){
                        if (dark_squares[l][0]==pos2[0] && dark_squares[l][1]==pos2[1]){
                            t1= true;
                        }
                    }
                    for (int lx = 0; lx < dark_squares.size(); lx = lx+1){
                        if (dark_squares[lx][0]==pos3[0] && dark_squares[lx][1]==pos3[1]){
                            t2=true;
                        }
                    }
                    if (t1&&t2){
                        vector<int> pos = {i, j};
                        circled_squares.push_back(pos);
                    }
                }
                if (i==1 && j==0){
                    t1 = false;
                    vector<int> pos = {i, j};
                    for (int l = 0; l < dark_squares.size(); l = l+1){
                        if (dark_squares[l][0]==pos[0] && dark_squares[l][1]==pos[1]){
                            t1= true;
                        }
                    }
                    if (t1){
                        vector<int> pos2 = {i-1, j+1};
                        circled_squares.push_back(pos2);
                    }                    
                }
                if (i==0 && j==1){
                    t1 = false;
                    vector<int> pos = {i, j};
                    for (int l = 0; l < dark_squares.size(); l = l+1){
                        if (dark_squares[l][0]==pos[0] && dark_squares[l][1]==pos[1]){
                            t1= true;
                        }
                    }
                    if (t1){
                        vector<int> pos2 = {i+1, j-1};
                        circled_squares.push_back(pos2);
                    }                    
                }
                if (i==grid_size[0]-2 && j==0){
                    t1 = false;
                    vector<int> pos = {i, j};
                    for (int l = 0; l < dark_squares.size(); l = l+1){
                        if (dark_squares[l][0]==pos[0] && dark_squares[l][1]==pos[1]){
                            t1= true;
                        }
                    }
                    if (t1){
                        vector<int> pos2 = {i+1, j+1};
                        circled_squares.push_back(pos2);
                    }                    
                }
                if (i==grid_size[0]-1 && j==1){
                    t1 = false;
                    vector<int> pos = {i, j};
                    for (int l = 0; l < dark_squares.size(); l = l+1){
                        if (dark_squares[l][0]==pos[0] && dark_squares[l][1]==pos[1]){
                            t1= true;
                        }
                    }
                    if (t1){
                        vector<int> pos2 = {i-1, j-1};
                        circled_squares.push_back(pos2);
                    }                    
                }
                if (i==0 && j==grid_size[1]-2){
                    t1 = false;
                    vector<int> pos = {i, j};
                    for (int l = 0; l < dark_squares.size(); l = l+1){
                        if (dark_squares[l][0]==pos[0] && dark_squares[l][1]==pos[1]){
                            t1= true;
                        }
                    }
                    if (t1){
                        vector<int> pos2 = {i+1, j+1};
                        circled_squares.push_back(pos2);
                    }                    
                }
                if (i==1 && j==grid_size[1]-1){
                    t1 = false;
                    vector<int> pos = {i, j};
                    for (int l = 0; l < dark_squares.size(); l = l+1){
                        if (dark_squares[l][0]==pos[0] && dark_squares[l][1]==pos[1]){
                            t1= true;
                        }
                    }
                    if (t1){
                        vector<int> pos2 = {i-1, j-1};
                        circled_squares.push_back(pos2);
                    }                    
                }
                if (i==grid_size[0]-2 && j==grid_size[1]-1){
                    t1 = false;
                    vector<int> pos = {i, j};
                    for (int l = 0; l < dark_squares.size(); l = l+1){
                        if (dark_squares[l][0]==pos[0] && dark_squares[l][1]==pos[1]){
                            t1= true;
                        }
                    }
                    if (t1){
                        vector<int> pos2 = {i+1, j-1};
                        circled_squares.push_back(pos2);
                    }                    
                }
                if (i==grid_size[0]-1 && j==grid_size[1]-2){
                    t1 = false;
                    vector<int> pos = {i, j};
                    for (int l = 0; l < dark_squares.size(); l = l+1){
                        if (dark_squares[l][0]==pos[0] && dark_squares[l][1]==pos[1]){
                            t1= true;
                        }
                    }
                    if (t1){
                        vector<int> pos2 = {i-1, j+1};
                        circled_squares.push_back(pos2);
                    }                    
                }
            }
        }
        for (int m = 0; m < dark_squares.size(); m=m+1){
            if (dark_squares[m][0]>0){
                vector<int> pos = {dark_squares[m][0]-1, dark_squares[m][1]};
                circled_squares.push_back(pos);
            }
            if (dark_squares[m][1]>0){
                vector<int> pos = {dark_squares[m][0], dark_squares[m][1]-1};
                circled_squares.push_back(pos);
            }
            if (dark_squares[m][0]<=grid_size[0]-2){
                vector<int> pos = {dark_squares[m][0]+1, dark_squares[m][1]};
                circled_squares.push_back(pos);
            }
            if (dark_squares[m][1]<=grid_size[1]-2){
                vector<int> pos = {dark_squares[m][0], dark_squares[m][1]+1};
                circled_squares.push_back(pos);
            }
        }
    }
    for(int j = 0; j < grid_size[1]; j=j+1){
        for(int i = 0; i < grid_size[0]; i=i+1){
            pos[0] = i*64;
            pos[1] = j*64;
            pos_[0] = pos[0]+24;
            pos_[1] = pos[1]+24;
            box.blit(pos, grid_surf);
            num = to_string(puzzle[j][i]);
            grid_text.render(num.c_str(), pos_,grid_surf);
        }
    }
    grid_image.init(grid_surf);
    int position[2] = {0, 0};
    for (int j = 0; j < circled_squares.size(); j = j+1){
        position[0] = circled_squares[j][0]*64;
        position[1] = circled_squares[j][1]*64;
        circle.blit(position, grid_surf);
    }
    int loc[2] = {0, 0};
    for (int j = 0; j < dark_squares.size(); j = j+1){
        position[0] = dark_squares[j][0]*64;
        position[1] = dark_squares[j][1]*64;
        loc[0] = position[0] + 24;
        loc[1] = position[1] + 24;
        darkbox.blit(position, grid_surf);
        num = to_string(puzzle[dark_squares[j][1]][dark_squares[j][0]]);
        grid_text.render(num.c_str(), loc,grid_surf, wColor);
    }
    int count = 0;
    int pos2[2] = {640-grid_size[0]*32, 360-grid_size[1]*32};
    while (playing){
        count += 1;
        window_surface = SDL_GetWindowSurface(win);
        SDL_FillRect(window_surface, &window_rect, white);
        button_state = SDL_GetMouseState(&mouse_pos[0], &mouse_pos[1]);
        mousepos = {mouse_pos[0], mouse_pos[1]};
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                playing = false;
            }
        }
        grid_image.blit(pos2);
        cursor_img.blit(mouse_pos);
        SDL_UpdateWindowSurface(win);
    }
    return 0;
}