import pygame

#pygame.transform.rotate(image, angle)

def main():
	pygame.init()
	screen = pygame.display.set_mode((240,180))
	image = pygame.image.load("ShortSword.png")
	screen.fill("white")
	screen.blit(image, (50,50))
	pygame.display.flip()
	input()

main()