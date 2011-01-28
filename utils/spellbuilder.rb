require 'rexml/document'
include REXML

class Spell
	attr_accessor :name, :fire, :ice
	def initialize(name)
		@name = name
	end
end

class Branch
end

class Tree
end

class Modifier
end

@types = ["spell", "branche", "tree", "modifier"]
@classes = [Spell, Branch, Tree, Modifier]

def generatexml(spells, branches, trees, modifiers, file)
	fp = open(file, "w")
	doc = Document.new
	doc.add_element("magicdata")
	[spells, branches, trees, modifiers].each_with_index do |type, i|
		temp = doc.root.add_element(@types[i]+"s")
		type.each do |element|
			temp2 = temp.add_element(@types[i])
			element.instance_variables.each do |var|
				temp2.add_element(var.gsub("@","")).text = element.instance_variable_get(var)
			end
		end
	end
	puts doc
	fp.write(doc)
	fp.close
end

def readxml(spells, branches, trees, modifiers, file, overwrite=false)
	if overwrite
		spells = []
		branches = []
		trees = []
		modifiers = []
	end
	if File.exists?(file)
		fp = File.open(file, "r")
		doc = Document.new(fp)
		doc.root.elements.each do |type|
			type.each do |element|
				puts element.class.inspect
				#element.each_element_with_attribute do |el, atr|
				#	puts el
				#	puts atr
				#end
			end
		end
		fp.close
	else
		puts '"#{file}" is not a valid file-name!'
	end
	
end

spells = []
branches = []
trees = []
modifiers = []

spells.push(Spell.new("fireball"))
spells.push(Spell.new("icebolt"))
spells[0].fire = "3"
spells[1].ice = "3"

generatexml(spells, branches, trees, modifiers, "test.xml")
readxml(spells, branches, trees, modifiers, "test.xml")

#builder.spells
#puts xml
