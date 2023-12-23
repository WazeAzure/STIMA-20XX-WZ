
        while(inp[i][j]){
            temp = temp * 10;
            if(inp[i][j] - '0' >= 0 && inp[i][j] - '0' <= 9){
                temp += inp[i][j] - '0';
            } else if(inp[i][j] == 'A'){
                temp += 1;
            } else if(inp[i][j] == 'J'){
                temp += 11;
            } else if(inp[i][j] == 'Q'){
                temp += 12;
            } else if(inp[i][j] == 'K'){
                temp += 13;
            }
            j++;
        }

        if(!(temp >= 1 && temp <= 13)){
            return 0;
        }
        
        j = 0;
        temp = 0;
    }
