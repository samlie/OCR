from PIL import Image, ImageDraw, ImageFont

img = Image.new('RGB', (600, 600), color = (73, 109, 137))


fnt = ImageFont.truetype('/usr/share/fonts/truetype/ubuntu-font-family/Ubuntu-B.ttf', 48)
d = ImageDraw.Draw(img)
d.text((5,5), "a b c d e f ghijklmnopq\n rstuvwxyz \n ABCDEFGHIJKLMPONSO \n JADIVNJZREOPJROJE \n *!:;='()m^&", font = fnt, fill=(255,255,0))

img.save('pil_text.bmp')
