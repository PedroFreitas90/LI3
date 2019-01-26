package engine;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;

import javax.xml.namespace.QName;
import javax.xml.stream.XMLEventReader;
import javax.xml.stream.XMLInputFactory;
import javax.xml.stream.XMLStreamException;
import javax.xml.stream.events.Attribute;
import javax.xml.stream.events.EndElement;
import javax.xml.stream.events.StartElement;
import javax.xml.stream.events.XMLEvent;
import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;
import java.time.LocalDate;
import java.util.HashMap;
import java.util.TreeSet;
import java.util.Set;

/**
 * Classe que efetua o parsing do ficheiro Posts.xml
 *
 * @author Grupo 51
 */
public class PostHandler extends DefaultHandler {

    private PostBD posts = null;
    private Post post = null;
    private HashMap<Integer,ArrayList<Post>> userposts = null;

    /**
     * Devolve a base de dados de posts
     * @return PostBD
     */
    public PostBD getPosts(){
        return posts;
    }

    /**
     * Devolve um conjunto que associa aos id's de users uma lista com os seus posts
     * @return HashMap<Integer,ArrayList<Post>>
     */
    public HashMap<Integer,ArrayList<Post>> getUserPosts(){
        return userposts;
    }

    
    @Override
    public void startElement(String uri, String localName, String qName, Attributes attributes) throws SAXException {

        if (qName.equalsIgnoreCase("row")) {

            Integer oid = 0;

            if (userposts == null)
                userposts = new HashMap<Integer,ArrayList<Post>>();

            post = new Post();

            String id = attributes.getValue("Id");
            if(id != null)
                post.setPostId(Integer.parseInt(id));

            String posttype = attributes.getValue("PostTypeId");
            if(posttype != null)
                post.setPostType(Integer.parseInt(posttype));

            String parentid = attributes.getValue("ParentId");
            if(parentid != null)
                post.setPostPid(Integer.parseInt(parentid));
            else post.setPostPid(-2);

            String score = attributes.getValue("Score");
            if(score != null)
                post.setPostScore(Integer.parseInt(score));

            String date = attributes.getValue("CreationDate");
            if(date != null)
                post.setPostDate(StringToLD(date));

            String viewcount = attributes.getValue("ViewCount");
            if(viewcount != null)
                post.setPostViewCount(Integer.parseInt(viewcount));
            else post.setPostViewCount(0);

            String ownerid = attributes.getValue("OwnerUserId");
            if(ownerid != null){
                oid = Integer.parseInt(ownerid);
                post.setPostOwner(oid);
            }

            String comcount = attributes.getValue("CommentCount");
            if(comcount != null)
                post.setPostNumCom(Integer.parseInt(comcount));

            String anscount = attributes.getValue("AnswerCount");
            if(anscount != null)
                post.setPostNumRes(Integer.parseInt(anscount));

            String title = attributes.getValue("Title");
            if(title != null)
                post.setPostTitle(title);

            String tags = attributes.getValue("Tags");
            if(tags != null)
                post.setPostTags(takeTag(tags));

            if(userposts.containsKey(oid))
                    userposts.get(oid).add(post.clone());
            else {
                ArrayList<Post> arr = new ArrayList<Post>();
                arr.add(post.clone());
                userposts.put(oid,arr);
            }

            if (posts == null)
                posts = new PostBD();
        }
    }

    @Override
    public void endElement(String uri, String localName, String qName) throws SAXException {
        if (qName.equalsIgnoreCase("row")) {
             posts.addPost(post);
        }
    }

    
    private static LocalDate StringToLD(String s){
        String aux = "";
        for (int i = 0; i < s.length() && s.charAt(i) != 'T'; i++)
            aux += s.charAt(i);
        LocalDate date= LocalDate.parse(aux);
        return date;
    }

    private static ArrayList<String> takeTag(String s){
        String aux;
        Set<String> auxret = new TreeSet<>();
        for (int i = 0; i < s.length(); i++){
            char c = s.charAt(i);
            aux = "";
            if(c == '<'){
                for(int j = i+1 ; j < s.length() && s.charAt(j) != '>'; j++){
                    c = s.charAt(j);
                    aux += c;
                }
            }
            auxret.add(aux);
        }
        ArrayList<String> ret = new ArrayList<>(auxret);
        return ret;
    }
    
}
