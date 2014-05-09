require 'unprof' if ARGV[0] == '--profile'


require 'rmagick'

#
# simple mandelbrot set using imagemagick
#

# settings
maxIterations = 25
factor = 512.0
res = [680.0, 420.0]

include Magick

image = Image.new(res[0], res[1]) do
  self.background_color = 'white'
end

# create canvas and fill colors
gradient = GradientFill.new(0, 0, 0, 100, '#00f', '#f00')
fill = Image.new(maxIterations, 1, gradient)
insideColor = Pixel.from_color('black')

# http://blade.nagaokaut.ac.jp/cgi-bin/scat.rb/ruby/ruby-talk/277157
def dot_product l1, l2
    sum = 0
    0.upto(l1.size - 1) do |i|
        sum += l1[i] * l2[i]
    end
    sum
end

c = []
aspect = res[0] / res[1]

# iterate through each pixel
image.each_pixel do |pixel, x, y|
  c[0] = (x / factor) - aspect
  c[1] = (y / factor) - 1.0
  z = c

  image.pixel_color(x, y, insideColor)

  maxIterations.times do |i|
    z[0] = (c[0] * c[0] - c[1] * c[1]) + c[0]
    z[1] = (c[0] * c[1] * 2.0) + c[1]
    
    if dot_product(z, z) > 5.0
      image.pixel_color(x, y, fill.pixel_color(i, 1))
      break
    end
  end
  
end

image.display

exit

