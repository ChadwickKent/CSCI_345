								if(spawning < 360) { //spawn path
									if(i < 8) {
										//set Y
										if(i < 4) {
											//set X
											if(spawning == 0) {
												grunt[i]->posX = 129 + (i * 40); //closest 30p off screen
												grunt[i]->posY = 370;
											} else if(spawning < 90) {
												grunt[i]->posX += 4;
												grunt[i]->posY -= 2;
											} else if(spawning < 150) {
												if(grunt[i]->posX > ((325 + (i * 40)) - 6) && grunt[i]->posX < ((325 + (i * 40)) + 6)) {
													grunt[i]->posX = 325 + (i * 40);
													grunt[i]->posY -= 2;
												}
												else {
													grunt[i]->posX -= 4;
													grunt[i]->posY -= 2;
												}
											}
										} else {
											//set X
											if(spawning == 0) {
												grunt[i]->posX = 690 + ((i - 4) * 40); //closest 30p off screen
												grunt[i]->posY = 370;
											} else if(spawning < 90) {
												grunt[i]->posX -= 4;
												grunt[i]->posY -= 2;
											} else if(spawning < 150) {
												if(grunt[i]->posX > ((325 + (i * 40)) - 6) && grunt[i]->posX < ((325 + (i * 40)) + 6))
													grunt[i]->posX = 325 + (i * 40);
												else
													grunt[i]->posX += 4;
												if(grunt[i]->posY > 70)
													grunt[i]->posY -= 2;
												else
													grunt[i]->posY = 70;
											}
										}
									}
									if(i < 16 && i > 7) {
										//set Y
										if(i < 12) {
											//set X
											if(spawning == 0) {
												grunt[i]->posX = 129 + ((i - 8) * 40); //closest 30p off screen
												grunt[i]->posY = 370;
											} else if(spawning > 60 && spawning < 150) {
												grunt[i]->posX += 4;
												grunt[i]->posY -= 2;
											} else if(spawning > 60 && spawning < 210) {
												if(grunt[i]->posX > ((325 + ((i - 8) * 40)) - 6) && grunt[i]->posX < ((325 + ((i - 8) * 40)) + 6))
													grunt[i]->posX = 325 + ((i - 8) * 40);
												else
													grunt[i]->posX -= 4;
												if(grunt[i]->posY > 112)
													grunt[i]->posY -= 2;
												else
													grunt[i]->posY = 112;
											}
										} else {
											//set X
											if(spawning == 0) {
												grunt[i]->posX = 690 + ((i - 12) * 40); //closest 30p off screen
												grunt[i]->posY = 370;
											} else if(spawning > 60 && spawning < 150) {
												grunt[i]->posX -= 4;
												grunt[i]->posY -= 2;
											} else if(spawning > 60 && spawning < 210) {
												if(grunt[i]->posX > ((325 + ((i - 8) * 40)) - 6) && grunt[i]->posX < ((325 + ((i - 8) * 40)) + 6))
													grunt[i]->posX = 325 + ((i - 8) * 40);
												else
													grunt[i]->posX += 4;
												if(grunt[i]->posY > 112)
													grunt[i]->posY -= 2;
												else
													grunt[i]->posY = 112;
											}
										}
									}
									if(i < 24 && i > 15) {
										//set Y
										if(i < 20) {
											//set X
											if(spawning == 0) {
												grunt[i]->posX = 129 + ((i - 16) * 40); //closest 30p off screen
												grunt[i]->posY = 370;
											} else if(spawning > 120 && spawning < 210) {
												grunt[i]->posX += 4;
												grunt[i]->posY -= 2;
											} else if(spawning > 120 && spawning < 270) {
												if(grunt[i]->posX > ((325 + ((i - 16) * 40)) - 6) && grunt[i]->posX < ((325 + ((i - 16) * 40)) + 6))
													grunt[i]->posX = 325 + ((i - 16) * 40);
												else
													grunt[i]->posX -= 4;
												if(grunt[i]->posY > 154)
													grunt[i]->posY -= 2;
												else
													grunt[i]->posY = 154;
											}
										} else {
											//set X
											if(spawning == 0) {
												grunt[i]->posX = 690 + ((i - 20) * 40); //closest 30p off screen
												grunt[i]->posY = 370;
											} else if(spawning > 120 && spawning < 210) {
												grunt[i]->posX -= 4;
												grunt[i]->posY -= 2;
											} else if(spawning > 120 && spawning < 270) {
												if(grunt[i]->posX > ((325 + ((i - 16) * 40)) - 6) && grunt[i]->posX < ((325 + ((i - 16) * 40)) + 6))
													grunt[i]->posX = 325 + ((i - 16) * 40);
												else
													grunt[i]->posX += 4;
												if(grunt[i]->posY > 154)
													grunt[i]->posY -= 2;
												else
													grunt[i]->posY = 154;
											}
										}
									}
									//325 + ((i * 40) - (320 * (i / 8))), 70 + (42 * (i / 8))
								} 
