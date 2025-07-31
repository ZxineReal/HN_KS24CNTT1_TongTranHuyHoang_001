#include<stdio.h>
#include<stdlib.h>
#define MAX 100

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        printf("Khong the cap phat bo nho dong!\n");
        return NULL;
    }
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node* insertNode(Node* node, int data) {
    if(node == NULL) {
        return createNode(data);
    }
    if (data < node->data) {
        node->left = insertNode(node->left, data);
    }
    if (data > node->data) {
        node->right = insertNode(node->right, data);
    }
    return node;
}

Node* findMin(Node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

Node* deleteNode(Node* root, int data) {
    if (root == NULL) {
        printf("Khong co gia tri nao trong cay!\n");
        return NULL;
    }
    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    } else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    } else {
        printf("Xoa thanh cong!\n");
        if (root->right == NULL) {
            free(root);
            return NULL;
        } else if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        } else {
            Node* temp = findMin(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }
    return root;
}

void inorder(Node* root) {
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

int countLeaves(Node* root) {
    if (root == NULL) {
        return 0;
    }
    if (root->left == NULL && root->right == NULL) {
        return 1;
    }
    return countLeaves(root->left) + countLeaves(root->right) + 1;
}

int height(Node* root) {
    if (root == NULL) {
        return 0;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int main() {
    Node* root = NULL;
    int choice;

    do {
        printf("---BINARY SEARCH TREE MANAGER---\n");
        printf("1. THEM GIA TRI\n");
        printf("2. XOA GIA TRI\n");
        printf("3. DUYET GIA TRI\n");
        printf("4. DEM LA\n");
        printf("5. CHIEU CAO\n");
        printf("6. THOAT\n");
        printf("Lua chon cua ban:\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                int x;
                printf("Moi ban nhap gia tri muon them vao cay:\n");
                scanf("%d", &x);
                root = insertNode(root, x);
                break;
            case 2:
                int deleteValue;
                printf("Moi ban nhap gia tri can xoa:\n");
                scanf("%d", &deleteValue);
                root = deleteNode(root, deleteValue);
                break;
            case 3:
                inorder(root);
                printf("\n");
                break;
            case 4:
                printf("So la trong cay la: %d\n", countLeaves(root));
                break;
            case 5:
                printf("Chieu cao cua cay la: %d \n", height(root));
                break;
            case 6:
                printf("Thoat chuong trinh!\n");
                return 0;
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while (choice != 6);
    return 0;
}