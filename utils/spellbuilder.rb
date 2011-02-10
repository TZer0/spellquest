require 'rexml/document'
include REXML

class GenericNameHolder
	def initialize(name)
		@name = name
	end
end

class Spell < GenericNameHolder
	attr_accessor :name, :fire, :ice
end

class Branch < GenericNameHolder
end

class Tree < GenericNameHolder
end

class Modifier < GenericNameHolder
end

@types = ["spell", "branch", "tree", "modifier"]
@classes = [Spell, Branch, Tree, Modifier]

def generatexml(spells, branches, trees, modifiers, file)
	if (file == nil or file == "")
		file = "spellinfo.xml"
	end
	fp = open(file, "w")
	doc = Document.new
	doc.add_element("magicdata")
	[spells, branches, trees, modifiers].each_with_index do |type, i|
		type.each do |element|
			temp = doc.root.add_element(@types[i])
			temp.attributes['id'] = element.name
			element.instance_variables.each do |var|
				if var == '@name'
					next
				end
				temp.add_element(var.gsub("@","")).text = element.instance_variable_get(var)
			end
		end
	end
	fp.write(doc)
	fp.close
end

def readxml(currentinfo, file, overwrite=false)
	if (file == nil or file == "")
		file = "spellinfo.xml"
	end
	if overwrite
		currentinfo = [[],[],[],[]]
	end
	if File.exists?(file)
		puts "Imported"
		fp = File.open(file, "r")
		doc = Document.new(fp)
		doc.root.each do |element|
			type = @types.find_index(element.name)
			temp = @classes[type].new(element.attributes['id'])
			element.each do |attrib|
				temp.instance_variable_set("@"+attrib.name, attrib.text)
			end
			currentinfo[type].push(temp)
		end
		fp.close
		return *currentinfo
	else
		puts '"#{file}" is not a valid file-name!'
	end
	
end

def listinfo(input, type)
	input.each_with_index do |element, i|
		puts type +" "+ i.to_s + ": "+ element.name
		element.instance_variables.each do |var|
			if var == '@name'
				next
			end
			puts var.gsub("@","") + ": " + element.instance_variable_get(var)
		end
		puts ""
	end
end

def getcat(input)
	@types.each_with_index do |type, i|
		if (input.downcase.slice(type))
			return i
		end
	end
	return -1
end

spells = []
branches = []
trees = []
modifiers = []

allinfo = [spells, branches, trees, modifiers]

spells.push(Spell.new("Fireball"))
spells.push(Spell.new("Icebolt"))
spells[0].fire = "3"
spells[1].ice = "3"

selected = -1
type = -1
while true
	print ">"
	input = gets
	i = getcat(input)
	if (input.downcase.slice("exit"))
		break
	elsif (input.downcase.slice("show"))
		if (i != -1)
			listinfo(allinfo[i], @types[i])
		else
			puts "Invalid category"
		end
	elsif (input.downcase.slice("delete"))
		if (i != -1)
			allinfo[i].delete_at((input.split(" ")[2]).to_i)
		else
			puts "Invalid category"
		end
	elsif (input.downcase.slice("import"))
		t = input.split(" ")
		spells, branches, trees, modifiers = readxml([spells, branches, trees, modifiers], t[1],  t[2]== "y")
	elsif (input.downcase.slice("export"))
		generatexml(spells, branches, trees, modifiers, input.split(" ")[1])
	elsif (input.downcase.slice("select"))
		t = input.split(" ")
		type = i
		selected = t[2].to_i
		if (allinfo[type][selected])
			puts @types[type] + " " + allinfo[type][selected].name + " selected"
		else
			type = -1
			selected = -1
			puts "Invalid selection"
		end
	elsif (input.downcase.slice("find"))
		t = input.split(" ")
		found = false
		allinfo[i].each_with_index do |element, j|
			if element.name.downcase == t[2].downcase
				puts "Found at index " + j.to_s
				type = i
				selected = j
				found = true
			end
		end
		if (not found)
			puts "Could not find"
		end
	end
end
