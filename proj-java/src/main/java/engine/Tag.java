package engine;

/**
 * Classe que contém a implementação da estrutura das Tags
 *
 * @author Grupo 51
 */

import java.util.ArrayList;
import java.time.LocalDate;

public class Tag {
    private long id;
    private String name;
    
    /**
     * Construtor vazio
     */
    public Tag(){
        this.id = -2;
        this.name = null;
    }

    /**
    * Construtor parametrizado
    *@param   long id da Tag.
    *@param   String nome da Tag.
    *@return  Tag criada.
    */
    public Tag(long id, String nome){
        this.id = id;
        this.name = nome;
    } 

    /**
     * Construtor por copia
     * @param Tag tags
     */
    public Tag(Tag t){
        this.id = t.getTagId();
        this.name = t.getTagName();
    }
    
    /**
     * Define o id da Tag
     * @param long id
     */
    public void setTagId(long id){
        this.id = id;
    }
    
    /**
     * Define o nome da Tag
     * @param String
     */
    public void setTagName(String n){
        this.name = n;
    }
    
    /**
     * Devolve o ID da tag
     * @return long
     */
    public long getTagId(){
        return this.id;
    }

    /**
     * Devolve o nome da tag
     * @return String
     */
    public String getTagName(){
        return this.name;
    }

    /**
    * Verifica a igualdade com outro objecto
    * @param Object
    * @return boolean
    */
    public boolean equals(Object cont){
        if (this == cont) return true;
        if ( (cont == null) || (this.getClass() != cont.getClass()) ) return false;
        Tag c = (Tag) cont;
        return (this.id == c.getTagId() && this.name.equals(c.getTagName()));
    }

    /**
     * Devolve uma cópia da instância
     * @return 
     */
    @Override
    public Tag clone(){
        return new Tag(this);
    }

}