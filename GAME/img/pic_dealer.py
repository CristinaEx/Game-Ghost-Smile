from PIL import Image
import numpy as np

def resize(pic_name,size = (960,640),save_name = 'test.png'):
    img = Image.open(pic_name)
    img = img.resize(size)
    img.save(save_name)

def cut(pic_name,x,y,width = 960,height = 640,save_name = 'test.png'):
    img = Image.open(pic_name)
    img = img.crop((x,y,x+width,y+height))
    img.save(save_name)

def transpose(pic_name,save_name = 'test.png'):
    img = Image.open(pic_name)
    out = img.transpose(Image.FLIP_LEFT_RIGHT) 
    out.save(save_name)

def toBlack(pic_name):
    img = Image.open(pic_name)
    width,height = img.size
    img = img.convert("L") 
    for h in range(height):
        for w in range(width):
            if img.getpixel((w,h)) < 100:
                img.putpixel((w,h),1)
            elif img.getpixel((w,h)) > 200:
                img.putpixel((w,h),255)
    img.show()
    img.save(pic_name)

if __name__ == '__main__':
    toBlack('left_player.jpg')
    