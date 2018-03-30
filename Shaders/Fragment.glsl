#version 330 core
out vec4 FragColor;  
in float ourColor;
  
void main()
{
// I send in a number that corresponds to the colour of the square
	if(ourColor.x ==0.1){
		FragColor = vec4(1.0,0.0,0.0, 1.0);
	}else if(ourColor.x ==0.2){
		FragColor = vec4(0.0,1.0,0.0, 1.0);
	}else if(ourColor.x ==0.3){
		FragColor = vec4(0.0,0.0,0.00, 1.0);
	}else if(ourColor.x ==0.4){
		FragColor = vec4(1.0,0.4,0.8, 1.0);
	}else{
		FragColor = vec4(0.0,0.52,1.0, 1.0);
	}
    
}