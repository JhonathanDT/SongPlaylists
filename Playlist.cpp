/**
 * @file playlist.cpp
 * @author Jhonathan Tepan (jhonathan.tepan51@myhunter.cuny.edu)
 * @brief This is the implementation file of the Playlist interface
 * @version 0.1
 * @date 2024-07-14
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "Playlist.hpp"

//default constructor  WORKS
Playlist::Playlist(){
    root_ptr_ = nullptr;
}
//WORKS copy constructor
Playlist::Playlist(const Playlist& other){
    root_ptr_ = copyTree(other.root_ptr_);
}
//WORKS private 
std::shared_ptr<SongNode> Playlist::copyTree(const std::shared_ptr<SongNode> old_tree_root_ptr)const{
    std::shared_ptr<SongNode> new_tree_ptr;
    //if the node we are copyingh is not null ptr 
    if(old_tree_root_ptr != nullptr){
        new_tree_ptr = std::make_shared<SongNode>(old_tree_root_ptr->song_ , old_tree_root_ptr -> artist_);
        //copy the left and right subtree
        new_tree_ptr ->left_ = copyTree(old_tree_root_ptr -> left_);
        new_tree_ptr -> right_ = copyTree(old_tree_root_ptr -> right_);
    }
    return new_tree_ptr;
}
//WORRKS move constructor
Playlist::Playlist(Playlist&& other){
    root_ptr_ = other.root_ptr_;
    other.root_ptr_.reset();
}

//copy assignment operator WORKS 
Playlist& Playlist::operator=(const Playlist& other){
    root_ptr_ = copyTree(other.root_ptr_);
    return *this;
}

//move assignment operator WORKS
Playlist& Playlist::operator=(Playlist&& other){
    root_ptr_ = other.root_ptr_;
    other.root_ptr_.reset();
    return *this;
}

//destructor works
Playlist::~Playlist(){
    destroyTree(root_ptr_);
    root_ptr_.reset();
}
//works (private)
void Playlist::destroyTree(std::shared_ptr<SongNode> sub_song_ptr){
    if(sub_song_ptr != nullptr){
        destroyTree(sub_song_ptr->left_);
        destroyTree(sub_song_ptr->right_);
        sub_song_ptr.reset();
    }
}
//works
void Playlist::clear(){
    destroyTree(root_ptr_);
    root_ptr_.reset();
}
//works
bool Playlist::isEmpty() const{
    return root_ptr_==nullptr;
}

//WORKS 
bool Playlist::add(const std::string& song, const std::string& artist){
    if(song != "" && artist != ""){
        auto new_songnode_ptr = std::make_shared<SongNode>(song,artist);
        root_ptr_ = placeNode(root_ptr_,new_songnode_ptr);
        return true;
        
    }
    return false;
}

//WORKS (private)
std::shared_ptr<SongNode> Playlist::placeNode(std::shared_ptr<SongNode> subtree_ptr, std::shared_ptr<SongNode> new_songnode_ptr){
    //if root == nullptr new_songnode_ptr becomes the root
    if(subtree_ptr == nullptr){
        return new_songnode_ptr; //base case
    }
    //place new_songnode to the left if it is less than or equal to the root node
    std::string song_and_artist_subtree = (subtree_ptr->song_) + (subtree_ptr->artist_);

    std::string song_and_artist_songNode = (new_songnode_ptr->song_) + (new_songnode_ptr->artist_);
    if( song_and_artist_subtree > song_and_artist_songNode ){
        subtree_ptr->left_ = placeNode(subtree_ptr->left_, new_songnode_ptr);
    }
    //place song node to the right subtree if node is greater than root item 
    else{ 
        subtree_ptr->right_ = placeNode(subtree_ptr-> right_, new_songnode_ptr);
    }
    return subtree_ptr;
}
//WORKS
size_t Playlist::getHeight() const{
    return getHeightHelper(root_ptr_);
}
//private WORKS
size_t Playlist::getHeightHelper(std::shared_ptr<SongNode> sub_song_ptr) const{
    //base cases
    if(sub_song_ptr == nullptr){
        return 0;
    }    
    return 1 + std::max(getHeightHelper(sub_song_ptr->left_) , getHeightHelper(sub_song_ptr->right_) );
}
// WORKS
size_t Playlist::getNumberOfSongs()const{
    size_t the_songs = getNumberOfSongsHelper(root_ptr_);
    return the_songs;
}
// private WORKS
size_t Playlist::getNumberOfSongsHelper( std::shared_ptr<SongNode> subtree_ptr) const{
    //base
    if(subtree_ptr == nullptr){
        return 0;
    }
    return 1 + getNumberOfSongsHelper(subtree_ptr -> left_) + getNumberOfSongsHelper(subtree_ptr -> right_);
}

bool Playlist::search(const std::string& name, const std::string& artist)const{

    if(searchHelper(root_ptr_, getKey(name, artist))){
        return true;
    }

    return false; 
}

bool Playlist::searchHelper( std::shared_ptr<SongNode> sub_song_ptr, const std::string key  )const{
    if( sub_song_ptr == nullptr){
        return false;
    }

    else if( getKey(*sub_song_ptr) == key ){
        return true;
    }

    else if( getKey(*sub_song_ptr) < key ){
        return searchHelper( sub_song_ptr -> right_ , key);
    }
    return searchHelper( sub_song_ptr -> left_ , key);
}


bool Playlist::remove(const std::string& song, const std::string& artist) {
    bool is_successful = false;
    root_ptr_ = removeValue(root_ptr_, song, artist, is_successful);
    return is_successful;
}

std::shared_ptr<SongNode> Playlist::removeValue(std::shared_ptr<SongNode> sub_tree, const std::string& song, const std::string& artist, bool& success) {
    // If subtree is empty, set success flag to false and return nullptr
    if (sub_tree == nullptr) {
        success = false;
        return sub_tree;
    }
    // If the current node matches the song and artist, remove the node and set success flag to true
    if (getKey(*sub_tree) == getKey(song,artist)) {
        sub_tree = removeNode(sub_tree);
        success = true;
        return sub_tree;
    }
    // Recursively search in the left subtree if the current node key is greater than the target song and artist
    if (getKey(*sub_tree) > getKey(song,artist)) {
        sub_tree -> left_ = removeValue(sub_tree -> left_, song, artist, success);
    }
    // Recursively search in the right subtree if the current node key is less than the target song and artist
    else {
        sub_tree -> right_ = removeValue(sub_tree -> right_, song, artist, success);
    }
    return sub_tree;
}


std::shared_ptr<SongNode> Playlist::removeNode(std::shared_ptr<SongNode> node_ptr) {
    // If the node is a leaf node, reset it and return nullptr
    if (node_ptr->isLeaf()) {
        node_ptr.reset();
        return node_ptr;
    }
    // If the left child is nullptr, return the right child
    else if (node_ptr -> left_ == nullptr) {
        return node_ptr -> right_;
    }
    // If the right child is nullptr, return the left child
    else if (node_ptr -> right_ == nullptr) {
        return node_ptr -> left_;
    }
    // If there are two children, find the leftmost node in the right subtree and replace the current node
    std::string inorder_song;
    std::string inorder_artist;
    node_ptr -> right_ = removeLeftmostNode(node_ptr -> right_, inorder_song, inorder_artist);
    node_ptr -> song_ = inorder_song;
    node_ptr -> artist_ = inorder_artist;
    return node_ptr;
}

// TODO: Remove this comment. DO NOT MODIFY THIS FUNCTION
std::shared_ptr<SongNode> Playlist::removeLeftmostNode(std::shared_ptr<SongNode> node_ptr, std::string& inorder_song, std::string& inorder_artist) {
    // If the left child is nullptr, store the song and artist, remove the current node
    if (node_ptr -> left_ == nullptr) {
        inorder_song = node_ptr -> song_;
        inorder_artist = node_ptr -> artist_;
        return removeNode(node_ptr);
    }
    // Recursively search for the leftmost node
    node_ptr -> left_ = removeLeftmostNode(node_ptr -> left_, inorder_song, inorder_artist);
    return node_ptr;
}

// TODO: Remove this comment. DO NOT MODIFY THIS FUNCTION
std::vector<SongNode> Playlist::inorderTraverse() const{
    std::vector<SongNode> result;
    inorderHelper(root_ptr_,result);
    return result;
}

// TODO: Remove this comment. DO NOT MODIFY THIS FUNCTION
void Playlist::inorderHelper(std::shared_ptr<SongNode> node_ptr, std::vector<SongNode>& result) const {
    // If node is not nullptr, add the node in the result vector following inorder traversal
    if (node_ptr != nullptr) {
        inorderHelper(node_ptr -> left_, result);
        result.push_back(*node_ptr);
        inorderHelper(node_ptr -> right_, result);
    }
}

std::vector<SongNode> Playlist::preorderTraverse() const{
    std::vector<SongNode> result;
    preorderHelper(root_ptr_, result);
    return result;
}

void Playlist::preorderHelper(std::shared_ptr<SongNode> node_ptr, std::vector<SongNode>& result) const{
    //if node is not nullptr, add the node in the result vector following preorder traversal 
    if(node_ptr != nullptr){
        result.push_back(*node_ptr);
        preorderHelper(node_ptr -> left_, result);
        preorderHelper(node_ptr -> right_, result);
    }
}

std::vector<SongNode> Playlist::postorderTraverse() const{
    std::vector<SongNode> result;
    postorderHelper(root_ptr_, result);
    return result;
}

void Playlist::postorderHelper(std::shared_ptr<SongNode> node_ptr, std::vector<SongNode>& result) const{
    //if node is not nullptr, add the node in the result vector following preorder traversal 
    if(node_ptr != nullptr){
        postorderHelper(node_ptr -> left_, result);
        postorderHelper(node_ptr -> right_, result);
        result.push_back(*node_ptr);
    }
}

// TODO: Remove this comment. DO NOT MODIFY THIS FUNCTION
std::string Playlist::getKey(const std::string& song, const std::string& artist) const {
    return song+artist;
}

// TODO: Remove this comment. DO NOT MODIFY THIS FUNCTION
std::string Playlist::getKey(const SongNode& song) const {
    return song.song_+song.artist_;
}