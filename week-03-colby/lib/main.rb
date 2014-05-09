
# "main" is a terrible name, I know.

require 'sinatra'
require 'sass'
require 'sqlite3'
require 'ostruct'

set :views, settings.root + '/../views'
set :public_folder, settings.root + '/../public'

error 404 do
  "ouch."
end

class Post
  attr_accessor :content, :created_at, :id
end

def connect_to_database
  SQLite3::Database.new('posts.db')
end

def get_query_objects(query_string)
  # connect to database, if needed.
  db ||= connect_to_database

  # get table columns
  cols = db.prepare(query_string).columns

  items = []

  begin
    db.results_as_hash = true
    db.execute query_string do |row|
      item = {}
      
      cols.each do |column|
        item[column] = row[column]
      end
      
      items << OpenStruct.new(item)
    end
  rescue SQLite3::SQLException => e
    e.message
  end
  
  items
end

def get_all(type, params = {})
  query = "SELECT * FROM #{type}"

  params[:sort]  && query += " ORDER BY #{params[:sort]}"
  params[:other] && query += " #{params[:other]}"
  params[:limit] && query += " LIMIT #{params[:limit]}"

  get_query_objects query
end

get '/build' do
  db = SQLite3::Database.new('posts.db')
  begin
    db.execute "CREATE TABLE posts (content TEXT , created_at INTEGER, id INTEGER PRIMARY KEY AUTOINCREMENT)"
    "Created posts table"
  rescue SQLite3::SQLException => e
    e
  end
end

get '/' do
  @posts = get_all :posts, { sort: "id DESC" }
  erb :index
end

get '/posts/:id' do
  @title = "View post"
  @needs_back = true
  @posts = get_all :posts, { limit: 1, other: "WHERE id=#{params[:id]}" }
  
  erb :index
end

post '/post/new' do
  db ||= connect_to_database
  begin
    db.execute("INSERT INTO posts (content, created_at) VALUES (?, ?)", params[:post_content], Time.now.to_i)
    redirect to '/'
  rescue SQLite3::SQLException => e
    e.message
  end
end

# XXX: I feel like there has to be a better way.
get '/css/style.css' do
  content_type 'text/css', :charset => 'utf-8'
  scss :style, :style => :expanded
end

"""
this file is public domain
- colby 
"""